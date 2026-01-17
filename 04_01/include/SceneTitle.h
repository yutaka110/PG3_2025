// SceneTitle.h
#pragma once
#include "Scene.h"

class SceneTitle : public IScene {
public:
	void Update(SceneManager& mgr, InputManager& input) override;
	void Draw() override;
};
