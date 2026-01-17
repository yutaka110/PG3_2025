#pragma once
#include <Novice.h>

class InputManager {
public:
	void Update() {
		// get keyboard state
		Novice::GetHitKeyStateAll(keys_);

		// update trigger
		for (int i = 0; i < 256; i++) {
			trigger_[i] = (keys_[i] != 0) && (prev_[i] == 0);
			prev_[i] = keys_[i];
		}
	}

	bool Press(int key) const { return keys_[key] != 0; }
	bool Trigger(int key) const { return trigger_[key]; }

private:
	char keys_[256] = {};
	char prev_[256] = {};
	bool trigger_[256] = {};
};
