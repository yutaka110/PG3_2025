// objects/Unit.cpp
#include "objects/Unit.h"
#include "Novice.h"
#include "objects/Selector.h"

void Unit::Draw() const {
	int size = 32;
	int px = x_ * size;
	int py = y_ * size;

	// 白枠
	Novice::DrawBox(px, py, size, size, 0.0f, 0xFFFFFFFF, kFillModeSolid);

	// 選択中なら薄赤で塗る（画像のピンクっぽい感じ）
	if (isSelected_) {
		Novice::DrawBox(px + 2, py + 2, size - 4, size - 4, 0.0f, 0xFFAAC8FF, kFillModeSolid);
	}
}

void Unit::Move(int dx, int dy) {
	x_ += dx;
	y_ += dy;
	if (x_ < 0) x_ = 0;
	if (y_ < 0) y_ = 0;
	if (x_ > 31) x_ = 31;
	if (y_ > 17) y_ = 17;
}

void Unit::MoveEnd(Selector* selector) {
	(void)selector;
	// 今回は必須じゃない（必要なら「UnitMode→SelectorMode」切替のトリガにする）
}
