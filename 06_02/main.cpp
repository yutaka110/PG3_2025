#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

static bool LoadCsvToGrid(const std::string& path, std::vector<std::vector<int>>& outGrid) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) return false;

    std::string line;
    std::vector<std::vector<int>> grid;

    while (std::getline(ifs, line)) {
        if (line.empty()) continue;

        std::vector<int> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            // 空セルは0扱い
            if (cell.empty()) {
                row.push_back(0);
            }
            else {
                row.push_back(std::stoi(cell));
            }
        }
        grid.push_back(row);
    }

    outGrid = std::move(grid);
    return true;
}

static char TileToChar(int v) {
    // マップチップの見た目をここで決める
    // 例 0=床 1=壁 2=ゴール 3=水 など
    switch (v) {
    case 0: return '.';
    case 1: return '#';
    case 2: return 'G';
    case 3: return '~';
    default: return '?';
    }
}

static void PrintMap(const std::vector<std::vector<int>>& grid) {
    if (grid.empty()) {
        std::cout << "map is empty\n";
        return;
    }

    std::cout << "map size: " << grid.size() << " x " << grid[0].size() << "\n";

    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            std::cout << TileToChar(grid[y][x]);
        }
        std::cout << "\n";
    }
}

int main(int argc, char** argv) {
    std::string path = "map.csv";
    if (argc >= 2) path = argv[1];

    std::mutex mtx;
    std::condition_variable cv;
    bool loaded = false;
    bool ok = false;
    std::vector<std::vector<int>> grid;

    // バックグラウンド読み込みスレッド
    std::thread loader([&] {
        std::vector<std::vector<int>> temp;
        bool success = LoadCsvToGrid(path, temp);

        {
            std::lock_guard<std::mutex> lock(mtx);
            ok = success;
            if (success) grid = std::move(temp);
            loaded = true;
        }
        cv.notify_one();
        });

    // メインスレッドは読み込み完了を待つ sleep等は使わない
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] { return loaded; });
    }

    loader.join();

    if (!ok) {
        std::cout << "failed to load csv: " << path << "\n";
        return 1;
    }

    // 読み込み後にマップ表示
    PrintMap(grid);
    return 0;
}
