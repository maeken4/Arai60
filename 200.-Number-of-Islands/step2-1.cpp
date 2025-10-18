#include <array>
#include <ranges>
#include <vector>
// 再帰によるDFS
class Solution {
  public:
    int numIslands(const std::vector<std::vector<char>>& grid) {
        const int num_rows = grid.size();
        const int num_cols = grid[0].size();
        std::vector<std::vector<bool>> visited_grid(num_rows, std::vector<bool>(num_cols, false));

        // これはだめ(C++17 brace elisionしてるのかpairの初期化なのか曖昧になるから？)
        // constexpr std::array<std::pair<int, int>, 4> direction{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        // これはOK
        // constexpr std::array<std::pair<int, int>, 4> direction = {{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};
        // またはvector
        const std::vector<std::pair<int, int>> direction = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        // (row, col)は有効なgridとし、(row, col)を始点として再帰的に探索する
        auto traverse_grid = [&](this auto self, const int row, const int col) -> void {
            if (visited_grid[row][col] || grid[row][col] == '0') {
                return;
            }
            visited_grid[row][col] = true;
            for (const auto [delta_row, delta_col] : direction) {
                const auto next_row = row + delta_col;
                const auto next_col = col + delta_row;
                if (0 <= next_row && next_row < num_rows && 0 <= next_col && next_col < num_cols) {
                    self(next_row, next_col);
                }
            }
        };

        int num_islands = 0;

        for (const auto row : std::views::iota(0, num_rows)) {
            for (const auto col : std::views::iota(0, num_cols)) {
                if (not visited_grid[row][col] && grid[row][col] == '1') {
                    ++num_islands;
                    traverse_grid(row, col);
                }
            }
        }
        return num_islands;
    }
};
