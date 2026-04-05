#include <queue>
#include <ranges>
#include <vector>

class Solution {
  public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
        int end_word_idx;
        for (const auto& [i, word] : std::views::enumerate(wordList)) {
            if (word == endWord) {
                end_word_idx = i;
                break;
            }
            // endWordがなかったら終了
            if (i == wordList.size() - 1) {
                return 0;
            }
        }
        // copy
        auto all_words = wordList;
        all_words.push_back(beginWord);

        int n = all_words.size();
        std::vector<std::vector<int>> graph(n);

        for (auto i : std::views::iota(0, n)) {
            for (auto j : std::views::iota(i + 1, n)) {
                if (is_adjacent(all_words[i], all_words[j])) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }

        return distance(n - 1, end_word_idx, graph) + 1;
    }

  private:
    bool is_adjacent(const std::string& s, const std::string& t) {
        int difference_count = 0;
        for (auto [c_s, c_t] : std::views::zip(s, t)) {
            if ((difference_count += (c_s != c_t)) > 1) {
                return false;
            }
        }
        return difference_count == 1;
    }

    // もし経路が存在しなければ-1を返す。
    int distance(int begin, int end, std::vector<std::vector<int>>& graph) {
        std::queue<int> visiting;
        std::vector<char> seen(graph.size(), 0);
        std::vector<int> distance_from_start(graph.size(), 0);
        visiting.push(begin);
        seen[begin] = 1;
        while (!visiting.empty()) {
            auto node = visiting.front();
            visiting.pop();
            seen[node] = 1;
            int distance_to_node = distance_from_start[node];
            if (node == end) {
                return distance_to_node;
            }
            for (auto next_node : graph[node]) {
                if (seen[next_node]) {
                    continue;
                }
                distance_from_start[next_node] = distance_to_node + 1;
                visiting.push(next_node);
                seen[next_node] = 1;
            }
        }
        return -1;
    }
};
