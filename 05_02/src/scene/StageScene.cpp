// scene/StageScene.cpp
#include "scene/StageScene.h"
#include "Novice.h"

void StageScene::Init() {
    selector_.Init();

    history_.clear();
    historyItr_ = history_.begin();
}

static void DeleteFrom(std::list<IStageSceneCommand*>& lst,
    std::list<IStageSceneCommand*>::iterator it) {
    while (it != lst.end()) {
        delete* it;
        it = lst.erase(it);
    }
}

void StageScene::Update() {
    input_.UpdateKeyState();

    // Undo（UnitModeだけ許可したいなら selector_.GetSelectMode() を見る）
    if (selector_.GetSelectMode() == UNIT_MODE && input_.IsUndoPressed()) {
        DoUndo();
        return;
    }

    IStageSceneCommand* cmd = nullptr;

    if (selector_.GetSelectMode() == SELECTOR_MODE) {
        cmd = input_.SelectorHandleInput(&selector_);
    }
    else {
        cmd = input_.UnitHandleInput(selector_.GetSelectedUnit(), &selector_);
    }

    if (!cmd) return;

    // Undo履歴を巻き戻したあとで新規コマンドが来たら「未来」を消す
    if (historyItr_ != history_.end()) {
        DeleteFrom(history_, historyItr_);
        historyItr_ = history_.end();
    }

    // 実行
    cmd->Exec();

    // Undo対象なら履歴に積む
    if (cmd->IsUndoable()) {
        history_.push_back(cmd);
        historyItr_ = history_.end();
    }
    else {
        delete cmd; // Undo対象外はその場で破棄
    }
}

void StageScene::DoUndo() {
    if (history_.empty()) return;

    // historyItr_ が end() のときは最後から戻す
    if (historyItr_ == history_.begin()) {
        // もう戻れない
        return;
    }

    // end() なら最後の要素へ、そうでなければ一つ前へ
    if (historyItr_ == history_.end()) {
        historyItr_ = history_.end();
    }
    auto it = historyItr_;
    --it;

    (*it)->Undo();
    historyItr_ = it; // ここまでUndo済み、という位置に移動
}

int StageScene::GetUndoRemain() const {
    // “これからUndoできる回数”＝historyItr_ までの要素数
    int n = 0;
    for (auto it = history_.begin(); it != historyItr_; ++it) n++;
    return n;
}

void StageScene::Draw() {

    // 背景（全画面）
    //Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xFF5A86B8, kFillModeSolid);

    // グリッド
    const int size = 32;
    for (int x = 0; x <= 1280; x += size) {
        Novice::DrawLine(x, 0, x, 720, 0x80FFFFFF);
    }
    for (int y = 0; y <= 720; y += size) {
        Novice::DrawLine(0, y, 1280, y, 0x80FFFFFF);
    }

    // セレクタ＆ユニット（背景の上）
    selector_.Draw();

    // UIの黒帯（下だけ）
    Novice::DrawBox(0, 620, 1280, 100, 0.0f, BLACK, kFillModeSolid);

    // 文字
    if (selector_.GetSelectMode() == SELECTOR_MODE) {
        Novice::ScreenPrintf(10, 640, "WASD||arrow keys: move / space key: change unit mode");
        Novice::ScreenPrintf(10, 660, "In Selector Mode, you cannot use the 'UnDo' action.");
    }
    else {
        Novice::ScreenPrintf(10, 640, "WASD||arrow keys: move / space key: change selector mode / ctrl+z: undo");
        Novice::ScreenPrintf(10, 660, "You have %d more 'UnDo' actions available.", GetUndoRemain());
    }
}
