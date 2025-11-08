#include <array>
#include <queue>
#include <ranges>
#include <vector>

class Solution {
  public:
    // 入力が不正な場合は-1を返す
    int maxAreaOfIsland(const std::vector<std::vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return -1;
        }
        num_rows = static_cast<int>(grid.size());
        num_cols = static_cast<int>(grid[0].size());

        int max_area_of_islands = 0;
        // 1はまだ探索していない島、0は海または探索済みの島
        std::vector<std::vector<int>> unvisited_islands = grid;
        for (const auto row : std::views::iota(0, num_rows)) {
            for (const auto col : std::views::iota(0, num_cols)) {
                if (unvisited_islands[row][col]) {
                    max_area_of_islands =
                        std::max(max_area_of_islands, measure_islands(row, col, unvisited_islands));
                }
            }
        }

        return max_area_of_islands;
    }

  private:
    int num_rows;
    int num_cols;
    const std::array<std::pair<int, int>, 4> direction = {{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};

    bool is_effective_grid(const int row, const int col) const {
        return 0 <= row && row < num_rows && 0 <= col && col < num_cols;
    }
    // 島の連結成分の面積を計算し訪問済みにする
    int measure_islands(const int start_row, const int start_col,
                        std::vector<std::vector<int>>& unvisited_islands) {
        int island_area = 0;
        std::queue<std::pair<int, int>> visiting;
        // BFS
        unvisited_islands[start_row][start_col] = 0;
        visiting.emplace(start_row, start_col);
        ++island_area;
        while (!visiting.empty()) {
            const auto [row, col] = visiting.front();
            visiting.pop();
            for (const auto [delta_row, delta_col] : direction) {
                const auto next_row = row + delta_row;
                const auto next_col = col + delta_col;
                if (is_effective_grid(next_row, next_col) && unvisited_islands[next_row][next_col]) {
                    unvisited_islands[next_row][next_col] = 0;
                    visiting.emplace(next_row, next_col);
                    ++island_area;
                }
            }
        }
        return island_area;
    }
};
