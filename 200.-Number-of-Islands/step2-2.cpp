#include <queue>
#include <ranges>
#include <vector>

// BFS
class Solution {
  public:
    int numIslands(std::vector<std::vector<char>> grid) {
        const int num_rows = grid.size();
        const int num_cols = grid[0].size();
        // {delta_row, delta_col}
        const std::vector<std::pair<int, int>> direction = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        int num_islands = 0;

        for (const auto row : std::views::iota(0, num_rows)) {
            for (const auto col : std::views::iota(0, num_cols)) {
                if (grid[row][col] == '0') {
                    continue;
                }
                ++num_islands;
                std::queue<std::pair<int, int>> next_visit_grids;
                next_visit_grids.push({row, col});
                while (!next_visit_grids.empty()) {
                    const auto [visid_row, visid_col] = next_visit_grids.front();
                    next_visit_grids.pop();
                    grid[visid_row][visid_col] = '0';
                    for (const auto [delta_row, delta_col] : direction) {
                        const auto next_row = visid_row + delta_row;
                        const auto next_col = visid_col + delta_col;
                        if (0 <= next_row && next_row < num_rows && 0 <= next_col && next_col < num_cols &&
                            grid[next_row][next_col] == '1') {
                            next_visit_grids.push({next_row, next_col});
                            grid[next_row][next_col] = '0';
                        }
                    }
                }
            }
        }

        return num_islands;
    }
};
