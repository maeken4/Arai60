
#include <stack>
#include <vector>

constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, 1, 0, -1};

// DFS
class Solution {
  public:
    int numIslands(const std::vector<std::vector<char>>& grid) {
        int island_nums = 0;
        const int h = grid.size();
        const int w = grid[0].size();
        std::vector<std::vector<bool>> seen_grid(h, std::vector<bool>(w, false));

        std::stack<std::pair<int, int>> visiting_stack;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (!seen_grid[i][j] && grid[i][j] == '1') {
                    visiting_stack.push({i, j});
                    ++island_nums;
                }
                while (!visiting_stack.empty()) {
                    const auto [y, x] = visiting_stack.top();
                    visiting_stack.pop();
                    seen_grid[y][x] = true;
                    for (int k = 0; k < 4; ++k) {
                        const int nx = x + dx[k];
                        const int ny = y + dy[k];
                        if (0 <= nx && nx < w && 0 <= ny && ny < h && !seen_grid[ny][nx] &&
                            grid[ny][nx] == '1') {
                            visiting_stack.push({ny, nx});
                        }
                    }
                }
            }
        }
        return island_nums;
    }
};
