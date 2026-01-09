// scene/StageSceneInputHandler.h
#pragma once
#include "commands/IStageSceneCommand.h"

class Selector;
class Unit;

class StageSceneInputHandler {
private:
	char keys_[256] = { 0 };
	char preKeys_[256] = { 0 };

public:
	void UpdateKeyState();

	IStageSceneCommand* SelectorHandleInput(Selector* selector);
	IStageSceneCommand* UnitHandleInput(Unit* unit, Selector* selector);

	bool IsUndoPressed() const; // Ctrl+Z
};
