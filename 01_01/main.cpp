#include <stdio.h>   // printf
#include <list>      // std::list(双方向リスト)
#include <initializer_list>
#include <string.h>
// ------------- 関数 -------------

// C文字列の配列から std::list<const char*> を作る
static std::list<const char*> make_list_from_array(const char* const* names, int count) {
	std::list<const char*> lst;
	for (int i = 0; i < count; ++i) {
		lst.push_back(names[i]);
	}
	return lst;
}

// リストを表示
static void print_list(const char* title, const std::list<const char*>& lst) {
	printf("=== %s ===\n", title);
	int i = 1;
	for (const char* name : lst) {
		printf("%2d. %s\n", i++, name);
	}
	printf("\n");
}

// 指定名の直後に駅を挿入
static void insert_after(std::list<const char*>& lst, const char* after, const char* name) {
	for (auto itr = lst.begin(); itr != lst.end(); ++itr) {

		if (strcmp(*itr, after) == 0) {
			lst.insert(std::next(itr), name);
			return;
		}
	}

	// 見つからなければ末尾
	lst.push_back(name);
}

// ------------- データ定義 -------------
static const char* YAMANOTE_1970[] = {
	"Tokyo",
	"Kanda",
	"Akihabara",
	"Okachimachi",
	"Ueno",
	"Uguisudani",
	"Nippori",
	// "西日暮里"
	"Tabata",
	"Komagome",
	"Sugamo",
	"Otsuka",
	"Ikebukuro",
	"Mejiro",
	"Takadanobaba",
	"Shin-Okubo",
	"Shinjuku",
	"Yoyogi",
	"Harajuku",
	"Shibuya",
	"Ebisu",
	"Meguro",
	"Gotanda",
	"Osaki",
	"Shinagawa",
	// "高輪ゲートウェイ"
	"Tamachi",
	"Hamamatsucho",
	"Shimbashi",
	"Yurakucho"
};

// ------------- メイン -------------
int main() {
	// 1970: 基本リストを作成
	std::list<const char*> y1970 = make_list_from_array(
		YAMANOTE_1970, (int)(sizeof(YAMANOTE_1970) / sizeof(YAMANOTE_1970[0]))
	);

	// 2019:1970に[Nishi-Nippori(1971開業)]を Nippori の直後に挿入
	std::list<const char*> y2019 = y1970;
	insert_after(y2019, "Nippori", "Nishi-Nippori");

	// 2022:2019に[Takanawa Gateway(2020開業)]を Shinagawa の直後に挿入
	std::list<const char*> y2022 = y2019;
	insert_after(y2022, "Shinagawa", "Takanawa Gateway");

	// 出力(英語表記)
	print_list("Yamanote Line stations (1970)", y1970);
	print_list("Yamanote Line stations (2019)", y2019);
	print_list("Yamanote Line stations (2022)", y2022);

	return 0;
}