#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

// 改行などを除去(in-place): std::string版
static void trim_newline(std::string& s) {
	while (!s.empty()) {
		char c = s.back();
		if (c == '\r' || c == '\n' || c == ' ' || c == '\t') {
			s.pop_back();
		}
		else {
			break;
		}
	}
}

static bool parse_k_g_numbers(const std::string& addr, int& outA, int& outB) {
	// 'k' を探す(先頭でなくてもOK)
	size_t kpos = addr.find('k');
	if (kpos == std::string::npos) return false;

	size_t i = kpos + 1;

	// kの後の数字(a)
	int a = 0; int da = 0;
	while (i < addr.size() && addr[i] >= '0' && addr[i] <= '9') {
		a = a * 10 + (addr[i] - '0');
		++i; ++da;
	}
	if (da == 0) return false;

	// 次が 'g'
	if (i >= addr.size() || addr[i] != 'g') return false;
	++i;

	// gの後の数字(b)
	int b = 0; int db = 0;
	while (i < addr.size() && addr[i] >= '0' && addr[i] <= '9') {
		b = b * 10 + (addr[i] - '0');
		++i; ++db;
	}
	if (db == 0) return false;

	outA = a;
	outB = b;
	return true;
}

// カンマ区切りsplit(string→vector<string>)
static void split_by_comma(const std::string& src, std::vector<std::string>& out) {
	size_t start = 0;
	while (start < src.size()) {
		size_t comma = src.find(',', start);
		if (comma == std::string::npos) comma = src.size();

		std::string token = src.substr(start, comma - start);
		trim_newline(token);
		if (!token.empty()) out.push_back(token);

		start = comma + 1;
	}
}

int main() {
	// 1) ifstreamで丸ごと読み込み(バイナリ推奨)
	std::ifstream ifs("PG3_2025_01_02.txt", std::ios::binary);
	if (!ifs) { printf("ファイルを開けません\n"); return 1; }

	// 2)　全文を std::string に読み込む
	std::string content(
		(std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>()
	);

	// 3) カンマで分割して std::vector<std::string>に格納
	std::vector<std::string> tokens;
	tokens.reserve(4096);
	split_by_comma(content, tokens);

	// 4) 数値順ソート(kの数字→gの数字→最後に辞書順)
	std::sort(tokens.begin(), tokens.end(),
		[](const std::string& a, const std::string& b) {
			int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
			bool pa = parse_k_g_numbers(a, a1, a2);
			bool pb = parse_k_g_numbers(b, b1, b2);

			if (pa && pb) {
				if (a1 != b1) return a1 < b1;
				if (a2 != b2) return a2 < b2;
				return a < b; // 最後は辞書順
			}
			return a < b; // 想定外フォーマットも辞書順
		}
	);

	// 5) 出力
	int i = 1;
	for (const std::string& addr : tokens) {
		printf("%3d. %s\n", i++, addr.c_str());
	}
	return 0;
}
