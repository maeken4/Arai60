#include <ranges>
#include <vector>

class Solution {
  public:
    int maxAreaOfIsland(std::vector<std::vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return -1;
        }

        num_rows = grid.size();
        num_cols = grid[0].size();
        unvisited_islands = grid;

        int result = 0;
        for (auto row : std::views::iota(0, num_rows)) {
            for (auto col : std::views::iota(0, num_cols)) {
                result = std::max(result, traverse_and_count_area(row, col));
            }
        }
        return result;
    }

  private:
    int num_rows;
    int num_cols;
    std::vector<std::vector<int>> unvisited_islands;
    int traverse_and_count_area(int row, int col) {
        if (!(0 <= row && row < num_rows && 0 <= col && col < num_cols)) {
            return 0;
        }
        if (unvisited_islands[row][col] == 0) {
            return 0;
        }

        unvisited_islands[row][col] = 0;
        return 1 + traverse_and_count_area(row + 1, col) + traverse_and_count_area(row, col + 1) +
               traverse_and_count_area(row - 1, col) + traverse_and_count_area(row, col - 1);
    }
};
