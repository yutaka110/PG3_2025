// scene/StageScene.h
#pragma once
#include <list>
#include "commands/IStageSceneCommand.h"
#include "objects/Selector.h"
#include "StageSceneInputHandler.h"

class StageScene {
private:
	StageSceneInputHandler input_;
	Selector selector_;

	std::list<IStageSceneCommand*> history_;
	std::list<IStageSceneCommand*>::iterator historyItr_;

public:
	void Init();
	void Update();
	void Draw();

	void DoUndo();
	int GetUndoRemain() const;
};
