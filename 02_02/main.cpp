#include <iostream>
#include <iomanip>
using namespace std;

// n時間目の時給を求める再帰関数
float GetRecursiveWage(int n) {

	// 最初の時給
	if (n == 1) return 100.0f;

	// 再帰的に計算
	return GetRecursiveWage(n - 1) * 2.0f - 50.0f;
}

int main() {

	// 一般的な時給
	const float normalWage = 1226.0f;

	// 計算する時間数
	const int hours = 10;
	cout << fixed << setprecision(0);

	// 累計金額を保持する変数
	float totalNormal = 0.0f;
	float totalRecursive = 0.0f;
	int crossoverHour = -1;

	cout << " 時間 | 一般的な時給 | 再帰的な時給 |   一般累計 |   再帰累計 " << endl;
	cout << "-----------------------------------------------------------" << endl;

	//---------------------------------------------
	// 各時間ごとの時給と累計を計算して表示
	//---------------------------------------------
	for (int i = 1; i <= hours; i++) {
		float wageRecursive = GetRecursiveWage(i);
		totalNormal += normalWage;
		totalRecursive += wageRecursive;

		if (crossoverHour == -1 && totalRecursive > totalNormal) {
			crossoverHour = i;
		}

		cout << setw(4) << i << "時間 | "
			<< setw(12) << normalWage << "円 | "
			<< setw(12) << wageRecursive << "円 | "
			<< setw(10) << totalNormal << "円 | "
			<< setw(10) << totalRecursive << "円"
			<< endl;
	}

	//---------------------------------------------
	// 結果をまとめて出力
	//---------------------------------------------
	cout << "\n--- 結果 ---" << endl;
	cout << "一般的な賃金体系の合計: " << totalNormal << "円\n";
	cout << "再帰的な賃金体系の合計: " << totalRecursive << "円\n";

	if (totalRecursive > totalNormal) {
		cout << "→ 再帰的な賃金体系の方が多い" << endl;
		if (crossoverHour != -1) {
			cout << crossoverHour << "時間目で逆転" << endl;
		}
	}
	else if (totalRecursive < totalNormal) {
		cout << "→ 一般的な賃金体系の方が多い" << endl;
	}
	else {
		cout << "→ 同額でした。" << endl;
	}

	return 0;
}
