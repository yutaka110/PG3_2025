// SceneClear.cpp
#include "../include/SceneClear.h"
#include "../include/SceneManager.h"
#include "../include/InputManager.h"
#include "../include/SceneTitle.h"
#include <Novice.h>

void SceneClear::Update(SceneManager& mgr, InputManager& input) {
	// press space to back to title
	if (input.Trigger(DIK_SPACE)) {
		mgr.Change(std::make_unique<SceneTitle>());
	}
}

void SceneClear::Draw() {
	Novice::ScreenPrintf(20, 20, "Clear");
	Novice::ScreenPrintf(20, 50, "Press SPACE to title");
}