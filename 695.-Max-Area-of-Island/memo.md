# step1
前回の問題とほとんど並列に進みそう。
グリッドを走査して最初に未発見の島を見つけたところからカウントをする。BFSとDFSどちらでもできそうだがいったんBFSで書く。

前回はseen_gridを用意していたが、gridをコピーして書き換えながら探索したかチェックする。

```cpp:step1.cpp
```

# step2

## 他の人のコードを読む
- early returnする書き方も自然で取り入れたい。 https://github.com/akmhmgc/arai60/pull/15/files#r2347265871

## Union Find
前回スルーしてしまったのでやってみる。
- odaさんの解説 https://discord.com/channels/1084280443945353267/1183683738635346001/1197738650998415500
- 参考にした実装 https://algo-logic.info/union-find-tree/

時間計算量は(m*n*α(m*n))　(alphaは逆アッカーマン関数)

```cpp:step2_union_find.cpp
#include <ranges>
#include <vector>

class DisjointUnionSet {
  private:
    const int n;
    std::vector<int> parents;
    std::vector<int> size;
    int find_root(int x) {
        if (parents[x] == x) {
            return x;
        }
        // path compression
        return parents[x] = find_root(parents[x]);
    }

  public:
    DisjointUnionSet(int n) : n(n), parents(n), size(n, 1) {
        for (auto i : std::views::iota(0, n)) {
            parents[i] = i;
        }
    }
    bool same(int x, int y) { return find_root(x) == find_root(y); }
    // return root of components of x and y after unite
    int unite(int x, int y) {
        x = find_root(x);
        y = find_root(y);
        if (x == y) {
            return x;
        }
        // union by size
        if (size[x] < size[y]) {
            std::swap(x, y);
        }
        parents[y] = x;
        size[x] += size[y];
        return x;
    }
    int size_of_components(int x) { return size[find_root(x)]; }
};

class Solution {
  public:
    int maxAreaOfIsland(const std::vector<std::vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return -1;
        }
        int num_rows = grid.size();
        int num_cols = grid[0].size();

        DisjointUnionSet connected_component_manager(num_rows * num_cols);
        for (auto row : std::views::iota(0, num_rows)) {
            for (auto col : std::views::iota(0, num_cols)) {
                if ((row + 1 < num_rows) && grid[row][col] == grid[row + 1][col]) {
                    connected_component_manager.unite(row * num_cols + col, (row + 1) * num_cols + col);
                }
                if ((col + 1 < num_cols) && grid[row][col] == grid[row][col + 1]) {
                    connected_component_manager.unite(row * num_cols + col, row * num_cols + col + 1);
                }
            }
        }

        int result = 0;
        for (auto row : std::views::iota(0, num_rows)) {
            for (auto col : std::views::iota(0, num_cols)) {
                if (grid[row][col] == 0) {
                    continue;
                }
                result =
                    std::max(result, connected_component_manager.size_of_components(row * num_cols + col));
            }
        }
        return result;
    }
};

```

## 自分用メモ
- 再帰を非再帰で書き直す https://qiita.com/KowerKoint/items/870ea9ef7a39f3fe4ce3
- CPU命令の時間比較　http://ithare.com/infographics-operation-costs-in-cpu-clock-cycles/


```cpp:step2.cpp
#include <ranges>
#include <vector>

class Solution {
  public:
    /**
     * 入力が空のグリッドの場合は-1を返す
     */
    int maxAreaOfIsland(const std::vector<std::vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return -1;
        }
        num_rows = static_cast<int>(grid.size());
        num_cols = static_cast<int>(grid[0].size());
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
    // 本来ならconstをつけてコンストラクタで初期化したほうがよい
    int num_rows;
    int num_cols;
    std::vector<std::vector<int>> unvisited_islands;

    int traverse_and_count_area(int row, int col) {
        if (!(0 <= row && row < num_rows && 0 <= col && col < num_cols)) {
            return 0;
        }
        if (!unvisited_islands[row][col]) {
            return 0;
        }
        // 訪れた
        unvisited_islands[row][col] = 0;
        return 1 + traverse_and_count_area(row + 1, col) + traverse_and_count_area(row, col + 1) +
               traverse_and_count_area(row - 1, col) + traverse_and_count_area(row, col - 1);
    }
};

```


# step3
```cpp:step3.cpp
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

```
