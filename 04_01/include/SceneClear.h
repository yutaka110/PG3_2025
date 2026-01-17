// SceneClear.h
#pragma once
#include "Scene.h"

class SceneClear : public IScene {
public:
	void Update(SceneManager& mgr, InputManager& input) override;
	void Draw() override;
};