#pragma once
class SceneManager;
class InputManager;

class IScene {
public:
	virtual ~IScene() = default;
	virtual void Update(SceneManager& mgr, InputManager& input) = 0;
	virtual void Draw() = 0;
};
