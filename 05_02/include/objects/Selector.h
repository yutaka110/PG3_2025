// objects/Selector.h
#pragma once
#include <vector>
#include "Unit.h"

enum SelectMode {
	SELECTOR_MODE,
	UNIT_MODE
};

class Selector {
private:
	int x_ = 0;
	int y_ = 0;
	SelectMode mode_ = SELECTOR_MODE;

	std::vector<Unit> units_;
	Unit* selectedUnit_ = nullptr;

public:
	void Init();
	void Draw() const;

	void Move(int dx, int dy);
	void SelectUnit();               // カーソル位置のユニットを選ぶ（あれば）
	void ReleaseUnit();              // UnitMode解除

	SelectMode GetSelectMode() const { return mode_; }
	Unit* GetSelectedUnit() const { return selectedUnit_; }
};
