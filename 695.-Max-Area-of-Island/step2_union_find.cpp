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
