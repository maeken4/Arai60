#include <ranges>
#include <vector>

class Solution {
  public:
    int numIslands(const std::vector<std::vector<char>>& grid) {
        const int num_rows = grid.size();
        if (num_rows == 0) {
            return 0;
        }
        const int num_cols = grid[0].size();

        std::vector<std::vector<bool>> seen_grid(num_rows, std::vector<bool>(num_cols, false));
        std::vector<std::pair<int, int>> direction = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        auto traverse_grid = [&](this auto self, const int row, const int col) -> void {
            seen_grid[row][col] = true;
            for (const auto [delta_row, delta_col] : direction) {
                const auto next_row = row + delta_row;
                const auto next_col = col + delta_col;
                if (0 <= next_row && next_row < num_rows && 0 <= next_col && next_col < num_cols &&
                    grid[next_row][next_col] == '1' && !seen_grid[next_row][next_col]) {
                    self(next_row, next_col);
                }
            }
        };

        int num_islands = 0;
        for (const auto row : std::views::iota(0, num_rows)) {
            for (const auto col : std::views::iota(0, num_cols)) {
                if (grid[row][col] == '0' || seen_grid[row][col]) {
                    continue;
                }
                ++num_islands;
                traverse_grid(row, col);
            }
        }
        return num_islands;
    }
};
