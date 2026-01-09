// objects/Selector.cpp
#include "objects/Selector.h"
#include "Novice.h"

void Selector::Init() {
    x_ = 0; y_ = 0;
    mode_ = SELECTOR_MODE;

    units_.clear();
    units_.resize(5);
    units_[0].Init(15, 1);
    units_[1].Init(7, 5);
    units_[2].Init(15, 5);
    units_[3].Init(26, 12);
    units_[4].Init(31, 9);

    selectedUnit_ = nullptr;
}

void Selector::Draw() const {

    Novice::ScreenPrintf(10, 10, "Selector::Draw called");

    // ユニット
    for (auto& u : units_) { u.Draw(); }

    // セレクタ赤枠
    int size = 32;
    int px = x_ * size;
    int py = y_ * size;
    Novice::DrawBox(px, py, size, size, 0.0f, RED, kFillModeWireFrame);
}

void Selector::Move(int dx, int dy) {
    x_ += dx; y_ += dy;
    if (x_ < 0) x_ = 0;
    if (y_ < 0) y_ = 0;
    if (x_ > 31) x_ = 31;
    if (y_ > 17) y_ = 17;
}

void Selector::SelectUnit() {
    // カーソル位置にいるUnitを探す
    for (auto& u : units_) {
        if (u.GetX() == x_ && u.GetY() == y_) {
            selectedUnit_ = &u;
            selectedUnit_->SetSelected(true);
            mode_ = UNIT_MODE;
            return;
        }
    }
}

void Selector::ReleaseUnit() {
    if (selectedUnit_) {
        selectedUnit_->SetSelected(false);
        selectedUnit_ = nullptr;
    }
    mode_ = SELECTOR_MODE;
}
