#include <map>
#include <queue>
#include <ranges>
#include <set>
#include <string>
#include <vector>

class Solution {
  public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
        auto end_word_idx = std::ranges::find(wordList, endWord) - wordList.begin();
        if (end_word_idx == wordList.size()) {
            return 0;
        }

        // グラフの代わり
        std::map<std::string, std::set<std::string>> pattern_to_matching_words;
        wordList.push_back(beginWord);  // 破壊的なのはまずい
        for (const auto& word : wordList) {
            if (beginWord.length() != word.length()) {
                // 入力で長さが異なることは保証されているが念のため
                continue;
            }
            for (int i = 0; i < word.length(); ++i) {
                auto pattern = word;  // copy
                pattern[i] = '*';
                pattern_to_matching_words[pattern].insert(word);
            }
        }

        // BFS
        std::map<std::string, int> seen_word_to_distance;
        std::queue<std::string> visiting;
        visiting.push(beginWord);
        seen_word_to_distance[beginWord] = 1;
        while (!visiting.empty()) {
            auto word = visiting.front();
            visiting.pop();
            int dist = seen_word_to_distance[word];
            if (word == endWord) {
                return dist;
            }
            for (int i = 0; i < word.length(); ++i) {
                auto pattern = word;
                pattern[i] = '*';
                for (const auto& next_word : pattern_to_matching_words[pattern]) {
                    if (!seen_word_to_distance.contains(next_word)) {
                        seen_word_to_distance[next_word] = dist + 1;
                        visiting.push(std::move(next_word));
                    }
                }
            }
        }

        return 0;
    }
};
