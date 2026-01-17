// SceneStage.cpp
#include "../include/SceneStage.h"
#include "../include/SceneManager.h"
#include "../include/InputManager.h"
#include "../include/SceneClear.h"
#include <Novice.h>
#include <algorithm>

void SceneStage::Update(SceneManager& mgr, InputManager& input) {
	// player move
	const float speed = 6.0f;
	if (input.Press(DIK_A))  px_ -= speed;
	if (input.Press(DIK_D)) px_ += speed;
	if (input.Press(DIK_W))    py_ -= speed;
	if (input.Press(DIK_S))  py_ += speed;

	// clamp
	px_ = std::clamp(px_, pr_, 1280.0f - pr_);
	py_ = std::clamp(py_, pr_, 720.0f - pr_);

	// shoot (single bullet)
	if (!bulletAlive_ && input.Trigger(DIK_SPACE)) {
		bulletAlive_ = true;
		bx_ = px_;
		by_ = py_ - pr_ - br_;
	}

	// bullet update
	if (bulletAlive_) {
		by_ -= 12.0f;
		if (by_ < -20.0f) {
			bulletAlive_ = false;
		}
	}

	// collision bullet vs enemy
	if (bulletAlive_) {
		for (int i = 0; i < 3; i++) {
			if (!enemyAlive_[i]) continue;
			if (HitCircle(bx_, by_, br_, ex_[i], ey_[i], er_[i])) {
				enemyAlive_[i] = false;
				bulletAlive_ = false;
				break;
			}
		}
	}

	// clear condition
	if (AliveEnemyCount() == 0) {
		mgr.Change(std::make_unique<SceneClear>());
	}
}

void SceneStage::Draw() {
	Novice::ScreenPrintf(20, 20, "Stage");
	Novice::ScreenPrintf(20, 50, "WASD keys: move");
	Novice::ScreenPrintf(20, 70, "SPACE: shoot");

	// player
	Novice::DrawEllipse((int)px_, (int)py_, (int)pr_, (int)pr_, 0.0f, 0xFFFFFFFF, kFillModeSolid);

	// bullet
	if (bulletAlive_) {
		Novice::DrawEllipse((int)bx_, (int)by_, (int)br_, (int)br_, 0.0f, 0xFFFFFFFF, kFillModeSolid);
	}

	// enemies
	for (int i = 0; i < 3; i++) {
		if (!enemyAlive_[i]) continue;
		Novice::DrawEllipse((int)ex_[i], (int)ey_[i], (int)er_[i], (int)er_[i], 0.0f, 0xFF00FFFF, kFillModeSolid);
	}
}
