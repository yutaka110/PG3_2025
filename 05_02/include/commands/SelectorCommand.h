// commands/stageScene/SelectorCommand.h
#pragma once
#include "IStageSceneCommand.h"

class Selector;

class SelectorMoveCommand : public IStageSceneCommand {
private:
	Selector* selector_;
	int dx_, dy_;
public:
	SelectorMoveCommand(Selector* selector, int dx, int dy);
	void Exec() override;
};

class SelectUnitCommand : public IStageSceneCommand {
private:
	Selector* selector_;
public:
	SelectUnitCommand(Selector* selector);
	void Exec() override;
};
