// commands/stageScene/UnitCommand.h
#pragma once
#include "IStageSceneCommand.h"

class Unit;
class Selector;

class UnitMoveCommand : public IStageSceneCommand {
private:
	Unit* unit_;
	int dx_, dy_;
public:
	UnitMoveCommand(Unit* unit, int dx, int dy);
	void Exec() override;

	bool IsUndoable() const override { return true; }
	void Undo() override; // 逆方向に戻す
};

class UnitMoveEndCommand : public IStageSceneCommand {
private:
	Unit* unit_;
	Selector* selector_;
public:
	UnitMoveEndCommand(Unit* unit, Selector* selector);
	void Exec() override;
};
