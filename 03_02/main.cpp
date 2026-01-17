#include <iostream>

//====================================
// 2つの型 T1, T2 を扱うクラステンプレート
// - メンバ関数 Min(a, b)で小さい方を返す
// - 返り値は「比較できて、どちらも代入できる型」に寄せるため double にする
//   (int/float/double の全組み合わせで確実に動く)
//====================================
template <typename T1, typename T2>
class MinBox {
public:
	double Min(T1 a, T2 b) {
		// 比較は double に揃えて行う(int/float/double の全組み合わせOK)
		double da = static_cast<double>(a);
		double db = static_cast<double>(b);
		return (da < db) ? da : db;
	}
};

int main() {
	//==============================
	// 3 + 3C2 = 6 パターン
	// 同型3つ + 異型3つ
	//==============================

	// int, int
	MinBox<int, int> m_ii;
	std::cout << "Min(int, int)= " << m_ii.Min(10, 3) << "\n";

	// float, float
	MinBox<float, float> m_ff;
	std::cout << "Min(float, float)= " << m_ff.Min(2.5f, 7.1f) << "\n";

	// double, double
	MinBox<double, double> m_dd;
	std::cout << "Min(double, double)= " << m_dd.Min(9.9, 1.2) << "\n";

	// int, float
	MinBox<int, float> m_if;
	std::cout << "Min(int, float)= " << m_if.Min(5, 3.2f) << "\n";

	// int, double
	MinBox<int, double> m_id;
	std::cout << "Min(int, double)= " << m_id.Min(8, 8.75) << "\n";

	// float, double
	MinBox<float, double> m_fd;
	std::cout << "Min(float, double)= " << m_fd.Min(6.4f, 6.39) << "\n";

	return 0;
}
