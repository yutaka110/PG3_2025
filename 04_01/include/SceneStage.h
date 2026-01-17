// SceneStage.h
#pragma once
#include "Scene.h"

class SceneStage : public IScene {
public:
	void Update(SceneManager& mgr, InputManager& input) override;
	void Draw() override;

private:
	// player
	float px_ = 640.0f;
	float py_ = 600.0f;
	float pr_ = 12.0f;

	// bullet (single)
	bool bulletAlive_ = false;
	float bx_ = 0.0f;
	float by_ = 0.0f;
	float br_ = 6.0f;

	// enemies (3)
	bool enemyAlive_[3] = { true, true, true };
	float ex_[3] = { 300.0f, 640.0f, 980.0f };
	float ey_[3] = { 160.0f, 120.0f, 160.0f };
	float er_[3] = { 18.0f, 18.0f, 18.0f };

private:
	static bool HitCircle(float ax, float ay, float ar, float bx, float by, float br) {
		float dx = ax - bx;
		float dy = ay - by;
		float rr = ar + br;
		return (dx * dx + dy * dy) <= (rr * rr);
	}

	int AliveEnemyCount() const {
		int c = 0;
		for (int i = 0; i < 3; i++) if (enemyAlive_[i]) c++;
		return c;
	}
};
