# step1
- ひとまずスタックでDFSを実装した。縦と横で混乱して案の定、grid[x][y]かgrid[y][x]かわからなくなる。
- 探索は右方向とした方向だけ見ればいいと勘違いしていたが、4方向に探索は進むため横向きのHのような島の場合に落ちていた。
- 書き方を覚えてやってる感があってよくない。。。
```cpp

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

```

# step2
他の人のプルリクを見る。
- https://github.com/tshimosake/arai60/pull/8
- https://github.com/sakupan102/arai60-practice/pull/18
- https://github.com/colorbox/leetcode/pull/31
  >これをメンバ変数で持つと、numIslands のスレッド並列性が失われます。失っては絶対にいけないわけではないですが、機能の複雑性とのバランスを考えたときに失うほどのものかとは思います。https://discord.com/channels/1084280443945353267/1237649827240742942/1265223555013152891

## 再帰によるDFS
gridを探索する再帰をメンバー関数にし、&gridをメンバー変数にしようと思ったが、constやら参照をつけるとややこしいらしい、、、
少なくともコンストラクタで初期化しないとだめで問題のインターフェイスと合わないので今回は無理に使わないことにする。
https://onihusube.hatenablog.com/entry/2018/10/23/010840

C++23から自己再帰するラムダを書きやすくなるようなのでこれを使った。
https://yohhoy.hatenadiary.jp/entry/20211025/p1

CSZAPでプログラムの動きを習ったので、再帰を使っても陽にスタックを使っても同じというのが実感できてよかった。
```cpp
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

```

## BFS
訪れた島は水に変えていくことでseen_gridが不要になる。実際の場面ではgridは巨大で参照で受け取りたいだろうし破壊的な実装は避けるべきだが、step1とstackとqueueを入れ替えただけになってしまうので今回はあえて破壊的に書いてみた。
```cpp
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

```

# step3
```cpp
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

```
