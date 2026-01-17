// SceneTitle.cpp
#include "../include/SceneTitle.h"
#include "../include/SceneManager.h"
#include "../include/InputManager.h"
#include "../include/SceneStage.h"
#include <Novice.h>

void SceneTitle::Update(SceneManager& mgr, InputManager& input) {
	// press space to start
	if (input.Trigger(DIK_SPACE)) {
		mgr.Change(std::make_unique<SceneStage>());
	}
}

void SceneTitle::Draw() {
	Novice::ScreenPrintf(20, 20, "Title");
	Novice::ScreenPrintf(20, 50, "Press SPACE to start");
}