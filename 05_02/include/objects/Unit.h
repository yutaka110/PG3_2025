#pragma once
// objects/Unit.h
#pragma once

class Selector;

class Unit {
private:
	int x_ = 0;
	int y_ = 0;
	bool isSelected_ = false;

public:
	void Init(int x, int y) { x_ = x; y_ = y; }
	void Draw() const;

	void SetSelected(bool b) { isSelected_ = b; }
	bool IsSelected() const { return isSelected_; }

	int GetX() const { return x_; }
	int GetY() const { return y_; }
	void SetPos(int x, int y) { x_ = x; y_ = y; }

	void Move(int dx, int dy);                 // Unit移動
	void MoveEnd(Selector* selector);          // Unit操作終了（必要なら）
};
