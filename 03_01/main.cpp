#include <iostream>
#include <cstddef>   // size_t

class Enemy {
public:
	Enemy()
		: phase_(Phase::Approach), timer_(0)
	{
	}

	void Update()
	{
		// 現在フェーズに対応する[メンバ関数]をテーブルから選んで呼ぶ
		const std::size_t idx = static_cast<std::size_t>(phase_);
		(this->*sPhaseFuncTable_[idx])();

		// フェーズに関係なく毎フレーム共通でやる処理(例デバッグ表示など)
		std::cout << "  [Debug] phase=" << PhaseName()
			<< ",timer=" << timer_ << "\n";
	}

private:
	// 状態'フェーズ)
	enum class Phase : std::size_t {
		Approach = 0,  // 接近
		Shoot = 1,   // 射撃
		Escape = 2,   // 離脱
		Count
	};

	// メンバ関数ポインタ型(Enemyのvoid関数を指す)
	using PhaseFunc = void (Enemy::*)();

	// ------------- フェーズごとの処理 -------------
	void PhaseApproach()
	{
		if (timer_ == 0) {
			std::cout << "[Enemy] 接近フェーズ開始\n";
		}

		std::cout << "[Enemy] 接近中\n";
		++timer_;

		//3回更新したら射撃へ
		if (timer_ >= 3) {
			ChangePhase(Phase::Shoot);
		}
	}

	void PhaseShoot()
	{
		if (timer_ == 0) {
			std::cout << "[Enemy]射撃フェーズ開始\n";
		}

		std::cout << "[Enemy](射撃)\n";
		++timer_;

		//2回撃ったら離脱へ
		if (timer_ >= 2) {
			ChangePhase(Phase::Escape);
		}
	}

	void PhaseEscape()
	{
		if (timer_ == 0) {
			std::cout << "[Enemy] 離脱フェーズ開始\n";
		}

		std::cout << "[Enemy] 離脱中\n";
		++timer_;

		//3回離脱したら接近へ戻す(ループ確認用)
		if (timer_ >= 3) {
			ChangePhase(Phase::Approach);
		}
	}

	// ------------- 共通処理 -------------
	void ChangePhase(Phase next)
	{
		phase_ = next;
		timer_ = 0;//次フェーズ用にカウンタをリセット
	}

	const char* PhaseName() const
	{
		switch (phase_) {
		case Phase::Approach: return "Approach";
		case Phase::Shoot:    return "Shoot";
		case Phase::Escape:   return "Escape";
		default:              return "Unknown";
		}
	}

private:
	Phase phase_;
	int timer_;

	// ------------- メンバ関数ポインタテーブル -------------
	static PhaseFunc sPhaseFuncTable_[static_cast<std::size_t>(Phase::Count)];
};

// テーブルの実体(ここが大事：クラス外で定義)
Enemy::PhaseFunc Enemy::sPhaseFuncTable_[static_cast<std::size_t>(Enemy::Phase::Count)] = {
	&Enemy::PhaseApproach, // Approach(0)
	&Enemy::PhaseShoot,    // Shoot(1)
	&Enemy::PhaseEscape    // Escape(2)
};

int main()
{
	Enemy enemy;

	//動作確認：何フレームか回す
	for (int frame = 0; frame < 15; ++frame) {
		std::cout << "\n=== Frame " << frame << " ===\n";
		enemy.Update();
	}

	return 0;
}
