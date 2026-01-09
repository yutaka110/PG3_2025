// commands/stageScene/UnitCommand.cpp
#include "commands/UnitCommand.h"
#include "objects/Unit.h"
#include "objects/Selector.h"

UnitMoveCommand::UnitMoveCommand(Unit* unit, int dx, int dy)
	: unit_(unit), dx_(dx), dy_(dy) {
}

void UnitMoveCommand::Exec() {
	unit_->Move(dx_, dy_);
}

void UnitMoveCommand::Undo() {
	unit_->Move(-dx_, -dy_);
}

UnitMoveEndCommand::UnitMoveEndCommand(Unit* unit, Selector* selector)
	: unit_(unit), selector_(selector) {
}

void UnitMoveEndCommand::Exec() {
	unit_->MoveEnd(selector_);
	selector_->ReleaseUnit();
}
