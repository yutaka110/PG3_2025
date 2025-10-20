#include <iostream>
#include <vector>
#include <iomanip> // setwやsetprecision用
using namespace std;

int main() {
    const float normalWage = 1226.0f;  // 一般的な時給
    const int hours = 10;              // 計算する時間数

    vector<float> normalWages;    // 一般的な時給（固定）
    vector<float> recursiveWages; // 再帰的な時給

    // 初期値設定
    for (int i = 0; i < hours; i++) {
        normalWages.push_back(normalWage);
    }
    recursiveWages.push_back(100.0f);

    // 2時間目以降を計算
    for (int i = 1; i < hours; i++) {
        float nextWage = recursiveWages.back() * 2.0f - 50.0f;
        recursiveWages.push_back(nextWage);
    }

    // 合計金額を計算しながら表示
    float totalNormal = 0.0f;
    float totalRecursive = 0.0f;

    cout << " 時間 | 一般的な時給 | 再帰的な時給 | 一般累計 | 再帰累計 " << endl;
    cout << "-----------------------------------------------" << endl;

    for (int i = 0; i < hours; i++) {
        totalNormal += normalWages[i];
        totalRecursive += recursiveWages[i];

        cout << setw(4) << i + 1 << "時間 | "
            << setw(10) << fixed << setprecision(0) << normalWages[i] << "円 | "
            << setw(10) << recursiveWages[i] << "円 | "
            << setw(8) << totalNormal << "円 | "
            << setw(8) << totalRecursive << "円" << endl;
    }

	// 結果表示
    cout << "\n--- 結果 ---" << endl;
    cout << "一般的な賃金体系の合計: " << totalNormal << "円\n";
    cout << "再帰的な賃金体系の合計: " << totalRecursive << "円\n";

    if (totalRecursive > totalNormal)
        cout << "→ 再帰的な賃金体系の方が多い！" << endl;
    else
        cout << "→ 一般的な賃金体系の方が多い。" << endl;

    return 0;
}
