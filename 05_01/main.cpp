#include <Novice.h>
#include <memory>
const char kWindowTitle[] = "LE2B_17_タケイ_ユタカ_タイトル";

// =========================================
// Receiver: commandを実行される側のオブジェクト
// =========================================
class Player {
public:
	void Init(float x, float y) {
		x_ = x;
		y_ = y;
	}

	void Move(float dx) {
		x_ += dx;

		// clamp (window 1280x720, size 32)
		if (x_ < 0.0f) x_ = 0.0f;
		if (x_ > 1280.0f - 32.0f) x_ = 1280.0f - 32.0f;
	}

	void Draw() const {
		Novice::DrawBox((int)x_, (int)y_, 32, 32, 0.0f, 0xFFFFFFFF, kFillModeSolid);
	}

private:
	float x_ = 0.0f;
	float y_ = 0.0f;
};

// =========================================
// Command interface
// =========================================
class ICommand {
public:
	virtual ~ICommand() = default;
	virtual void Execute(Player& target) = 0;
};

// =========================================
// Concrete commands
// =========================================
class MoveLeftCommand : public ICommand {
public:
	explicit MoveLeftCommand(float speed) : speed_(speed) {}
	void Execute(Player& target) override {
		target.Move(-speed_);
	}
private:
	float speed_ = 0.0f;
};

class MoveRightCommand : public ICommand {
public:
	explicit MoveRightCommand(float speed) : speed_(speed) {}
	void Execute(Player& target) override {
		target.Move(speed_);
	}
private:
	float speed_ = 0.0f;
};

// =========================================
// Invoker: input -> command生成 -> execute
// =========================================
class InputManager {
public:
	void Update() {
		Novice::GetHitKeyStateAll(keys_);
		for (int i = 0; i < 256; i++) {
			trigger_[i] = (keys_[i] != 0) && (prev_[i] == 0);
			prev_[i] = keys_[i];
		}
	}

	bool Press(int key) const { return keys_[key] != 0; }
	bool Trigger(int key) const { return trigger_[key]; }

private:
	char keys_[256] = {};
	char prev_[256] = {};
	bool trigger_[256] = {};
};

class CommandInvoker {
public:
	// inputからcommandを決めて返す(必要なら毎フレーム作るだけでOK)
	std::unique_ptr<ICommand> CreateCommand(const InputManager& input) const {
		const float speed = 6.0f;

		// A or Left
		if (input.Press(DIK_A) || input.Press(DIK_LEFT)) {
			return std::make_unique<MoveLeftCommand>(speed);
		}

		// D or Right
		if (input.Press(DIK_D) || input.Press(DIK_RIGHT)) {
			return std::make_unique<MoveRightCommand>(speed);
		}

		return nullptr;
	}

	// commandをexecuteする役
	void ExecuteIfExists(std::unique_ptr<ICommand> cmd, Player& player) const {
		if (cmd) {
			cmd->Execute(player);
		}
	}
};


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	InputManager input;
	CommandInvoker invoker;

	Player player;
	player.Init(200.0f, 120.0f);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		input.Update();

		// create command from input, then execute on receiver
		auto cmd = invoker.CreateCommand(input);
		invoker.ExecuteIfExists(std::move(cmd), player);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		// draw
		player.Draw();

		Novice::ScreenPrintf(20, 20, "Move: A/D or Left/Right");
		Novice::ScreenPrintf(20, 40, "ESC: Exit");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
