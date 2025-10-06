#include <iostream>
#include <algorithm>

int Min(int a, int b) {
	return std::min(a, b);
}

float Min(float a, float b) {
	return std::min(a, b);
}

double Min(double a, double b) {
	return std::min(a, b);
}

template <typename T>
T Min(T a, T b) {
	return std::min(a, b);
}


int main() {

	// int型の比較
	std::cout << "int型の小さい方: " << Min(18, 22) << std::endl;

	// float型の比較（末尾の f が float 型を意味する）// float型の比較（末尾の f が float 型を意味する）
	std::cout << "float型の小さい方: " << Min(1.6f, 3.2f) << std::endl;

	// double型の比較（小数点だけなら double 型と推論される）
	std::cout << "double型の小さい方: " << Min(2.4, 4.8) << std::endl;

	
	return 0;
}