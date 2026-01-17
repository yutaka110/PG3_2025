#pragma once
// SceneManager.h
#pragma once
#include <memory>
#include "Scene.h"

class SceneManager {
public:
	void Change(std::unique_ptr<IScene> next) {
		next_ = std::move(next);
	}

	void ApplyChangeIfNeeded() {
		if (next_) {
			current_ = std::move(next_);
		}
	}

	IScene* Get() { return current_.get(); }

private:
	std::unique_ptr<IScene> current_;
	std::unique_ptr<IScene> next_;
};
