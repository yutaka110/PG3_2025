// commands/stageScene/SelectorCommand.cpp
#include "commands/SelectorCommand.h"
#include "objects/Selector.h"

SelectorMoveCommand::SelectorMoveCommand(Selector* selector, int dx, int dy)
	: selector_(selector), dx_(dx), dy_(dy) {
}

void SelectorMoveCommand::Exec() {
	selector_->Move(dx_, dy_);
}

SelectUnitCommand::SelectUnitCommand(Selector* selector)
	: selector_(selector) {
}

void SelectUnitCommand::Exec() {
	selector_->SelectUnit();
}
