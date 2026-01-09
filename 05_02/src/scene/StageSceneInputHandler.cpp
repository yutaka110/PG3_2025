// scene/StageSceneInputHandler.cpp
#include "scene/StageSceneInputHandler.h"
#include "Novice.h"
#include "objects/Selector.h"
#include "objects/Unit.h"
#include "commands/SelectorCommand.h"
#include "commands/UnitCommand.h"

void StageSceneInputHandler::UpdateKeyState() {
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);
}

static bool Pressed(const char* keys, const char* pre, int key) {
	return keys[key] && !pre[key];
}

IStageSceneCommand* StageSceneInputHandler::SelectorHandleInput(Selector* selector) {
	// 移動（WASD or Arrow）
	if (Pressed(keys_, preKeys_, DIK_W) || Pressed(keys_, preKeys_, DIK_UP))    return new SelectorMoveCommand(selector, 0, -1);
	if (Pressed(keys_, preKeys_, DIK_S) || Pressed(keys_, preKeys_, DIK_DOWN))  return new SelectorMoveCommand(selector, 0, 1);
	if (Pressed(keys_, preKeys_, DIK_A) || Pressed(keys_, preKeys_, DIK_LEFT))  return new SelectorMoveCommand(selector, -1, 0);
	if (Pressed(keys_, preKeys_, DIK_D) || Pressed(keys_, preKeys_, DIK_RIGHT)) return new SelectorMoveCommand(selector, 1, 0);

	// Spaceでユニット選択（ユニットがそこにいれば UNIT_MODEへ）
	if (Pressed(keys_, preKeys_, DIK_SPACE)) return new SelectUnitCommand(selector);

	return nullptr;
}

IStageSceneCommand* StageSceneInputHandler::UnitHandleInput(Unit* unit, Selector* selector) {
	// Unit移動（Undo対象）
	if (Pressed(keys_, preKeys_, DIK_W) || Pressed(keys_, preKeys_, DIK_UP))    return new UnitMoveCommand(unit, 0, -1);
	if (Pressed(keys_, preKeys_, DIK_S) || Pressed(keys_, preKeys_, DIK_DOWN))  return new UnitMoveCommand(unit, 0, 1);
	if (Pressed(keys_, preKeys_, DIK_A) || Pressed(keys_, preKeys_, DIK_LEFT))  return new UnitMoveCommand(unit, -1, 0);
	if (Pressed(keys_, preKeys_, DIK_D) || Pressed(keys_, preKeys_, DIK_RIGHT)) return new UnitMoveCommand(unit, 1, 0);

	// SpaceでSelectorModeに戻る
	if (Pressed(keys_, preKeys_, DIK_SPACE)) return new UnitMoveEndCommand(unit, selector);

	return nullptr;
}

bool StageSceneInputHandler::IsUndoPressed() const {
	bool ctrl = keys_[DIK_LCONTROL] || keys_[DIK_RCONTROL];
	bool z = Pressed(keys_, preKeys_, DIK_Z);
	return ctrl && z;
}
