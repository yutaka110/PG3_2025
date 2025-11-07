#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>   
#include <chrono>
#include <functional>
using namespace std;

//サイコロの出目を遅延表示する関数
void DelayReveal(function<void(int, int)> fn, unsigned int delayMs, int roll, int userGuess) {
	cout << "サイコロを振っています";

	//指定時間待つ
	this_thread::sleep_for(chrono::milliseconds(delayMs));
	cout << endl;

	//コールバック呼び出し
	fn(roll, userGuess);
}

int main() {
	srand((unsigned)time(NULL));

	int userGuess;
	cout << "サイコロの出目が半(奇数)か丁(偶数)かを当ててください。\n";
	cout << "半(奇数)=1, 丁(偶数)=0 を入力: ";
	cin >> userGuess;

	int roll = rand() % 6 + 1;

	//ラムダ式で定義
	auto showResult = [](int roll, int userGuess) {
		cout << "サイコロの出目は " << roll << " でした。\n";
		int isOdd = roll % 2;
		if (isOdd == userGuess)
			cout << "正解です\n";
		else
			cout << "不正解です\n";
		};

	//ラムダ式をDelayRevealに渡す
	DelayReveal(showResult, 3000, roll, userGuess);

	return 0;
}
