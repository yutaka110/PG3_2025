#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdio>

int main() {
	std::mutex mtx;
	std::condition_variable cv;

	// 誰の番か 1->2->3
	int turn = 1;

	// それぞれのスレッドが自分の番になるまで待って表示する
	auto worker = [&](int id) {
		std::unique_lock<std::mutex> lock(mtx);

		// 自分の番になるまで待機 sleep等は使わず 条件変数で待つ
		cv.wait(lock, [&] { return turn == id; });

		// ここに来た時点で turn == id が保証される
		std::printf("thread %d\n", id);

		// 次の番へ
		++turn;

		// 他のスレッドを起こす
		cv.notify_all();
		};

	// std::thread を必ず使って並列に起動
	std::thread t1(worker, 1);
	std::thread t2(worker, 2);
	std::thread t3(worker, 3);

	// 終了待ち
	t1.join();
	t2.join();
	t3.join();

	return 0;
}