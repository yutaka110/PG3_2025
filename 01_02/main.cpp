#include <stdio.h>
#include <list>
#include <string.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iterator>

// 改行などを除去（in-place）
static void trim_newline(char* s) {
    char* end = s + strlen(s);
    while (end > s && (end[-1] == '\r' || end[-1] == '\n' || end[-1] == ' ' || end[-1] == '\t'))
        *--end = '\0';
}

// k###g#### を数値抽出（例: k024g1017@... → outA=24, outB=1017）
static bool parse_k_g_numbers(const char* addr, int& outA, int& outB) {
    const char* p = addr;
    while (*p && *p != 'k') ++p;
    if (*p != 'k') return false; ++p;

    int a = 0; int da = 0;
    while (*p >= '0' && *p <= '9') { a = a * 10 + (*p - '0'); ++p; ++da; }
    if (*p != 'g' || da == 0) return false; ++p;

    int b = 0; int db = 0;
    while (*p >= '0' && *p <= '9') { b = b * 10 + (*p - '0'); ++p; ++db; }
    if (db == 0) return false;  // '@'チェックは不要（末尾に改行等があってもOK）

    outA = a; outB = b; return true;
}

int main() {
    // 1) ifstreamで丸ごと読み込み（バイナリ推奨）
    std::ifstream ifs("PG3_2025_01_02.txt", std::ios::binary);
    if (!ifs) { printf("ファイルを開けません\n"); return 1; }

    std::vector<char> buffer((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());
    buffer.push_back('\0'); // NUL終端を付ける

    // 2) カンマで分割（破壊的分割）してポインタだけ保持
    std::vector<const char*> tokens;
    tokens.reserve(4096);

    char* context = nullptr;
    char* token = strtok_s(buffer.data(), ",", &context);
    while (token) {
        trim_newline(token);
        if (*token) tokens.push_back(token);
        token = strtok_s(nullptr, ",", &context);
    }

    // 3) 数値順ソート（kの数字→gの数字→最後に辞書順）
    std::sort(tokens.begin(), tokens.end(), [](const char* a, const char* b) {
        int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
        bool pa = parse_k_g_numbers(a, a1, a2);
        bool pb = parse_k_g_numbers(b, b1, b2);
        if (pa && pb) {
            if (a1 != b1) return a1 < b1;
            if (a2 != b2) return a2 < b2;
            return strcmp(a, b) < 0;
        }
        return strcmp(a, b) < 0; // 想定外フォーマットは辞書順
        });

    // 4) 出力（必要なら std::list に詰め替えてもOK）
    int i = 1;
    for (const char* addr : tokens) {
        printf("%3d. %s\n", i++, addr);
    }
    return 0;
}
