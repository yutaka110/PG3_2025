#include <Novice.h>
#include "include/SceneManager.h"
#include "include/InputManager.h"
#include "include/SceneTitle.h"

const char kWindowTitle[] = "LE2B_17_タケイ_ユタカ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	InputManager input;
	SceneManager sceneMgr;

	// start scene
	sceneMgr.Change(std::make_unique<SceneTitle>());
	sceneMgr.ApplyChangeIfNeeded();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// update input
		input.Update();

		// update scene
		if (sceneMgr.Get()) {
			sceneMgr.Get()->Update(sceneMgr, input);
		}

		// apply scene change at safe timing
		sceneMgr.ApplyChangeIfNeeded();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// draw scene
		if (sceneMgr.Get()) {
			sceneMgr.Get()->Draw();
		}


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
