// commands/stageScene/IStageSceneCommand.h
#pragma once

class IStageSceneCommand {
public:
	virtual ~IStageSceneCommand() = default;
	virtual void Exec() = 0;

	// Undo対応（必要最小）
	virtual bool IsUndoable() const { return false; }
	virtual void Undo() {} // Undoableだけoverride
};
