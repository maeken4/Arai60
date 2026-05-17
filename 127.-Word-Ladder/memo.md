# step1
なんか制約とか条件がすっきりしてなくわかりにくい…
- endwordはwordlistに入っている必要がある(入っているとは言っていない?)。
- beginwordは入っているかもしれないし入っていないかもしれない
- beginword.len = endword.lenは保証されている。
単語を頂点、遷移できるときに辺を考えれば最短経路の問題に帰着しそう。
各単語の長さをL, 単語数をNとすると、グラフ構築にO(N^2*L), BFSにO(N)でグラフ構築のほうに時間がかかりそう。
847msですごく遅いように見える。

```cpp:step1.cpp
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

```

# step2
他の人のコードを読む
- https://github.com/goto-untrapped/Arai60/pull/57#discussion_r1781365485
    > 大まかな方針として、
    wordAndLengths という Queue を用意して、(beginWord, 1) という組をいれる。
    そして、Queue から出てきたものを記録する usedWords を用意する。
    以下を繰り返す。『
    Queue から「単語と距離」の組を取り出す。endWord が出てきたら完了で適切に答えを返す。
    その単語の隣接する単語で usedWords に入っていないやつを Queue に突っ込み usedWords にする。距離は1増やしておく。』
    くらいで、あとは、隣接する単語を列挙するための前計算と本計算があるんですよね。
    とりあえず、前計算と本計算は、関数で分離してみましょう。そうすると別にテストができるはずです。
    つまり、何かをしようとして、そのことを覚えておきながら別のことをしようとすると、覚えておかないといけないので混乱するんですよね。

- https://github.com/shining-ai/leetcode/pull/20#discussion_r1517026158
    > この関数は２つの文字列の違いが1文字かどうかを返していると思うのですが、2つの文字列の違いのことをhamming distanceと呼びEdit Distanceの一種です。他にはLevenshtein distanceなどがあります。こちらは2つの文字列の距離を追加、削除、置換のオペレーションの数で表します。テキストエディタとかのauto correction機能とかで使われます。

    編集距離の使い道を知らなかった。

https://github.com/tarinaihitori/leetcode/pull/20

https://github.com/docto-rin/leetcode/pull/19



考えると単語の長さもチェックする必要がありそう。->一応問題文で保障されている
文字列のビューを使う
イテレーターを使う
パターンを使う
size() length()　文字列の場合使い分ける？
beginwordとendwordの変な非対称はこういう解法があるからなのね


## step2-1
パターンで引く方法

時間計算量: 各単語に対してL個のパターン生成とそれぞれで文字列コピーでO(N*L^2)

空間計算量: O(N*L)
```cpp:step2-1.cpp
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
        for (const auto& word : wordList) {
            if (beginWord.length() != word.length()) {
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

```


## step2-2
文字列集合が小さいことを使った方法

時間計算量: BFSで各単語を訪問し、各文字に対して26通り見るので O(26\*N\*L)

空間計算量: O(N*L)

```cpp:step2-2.cpp
#include <queue>
#include <string>
#include <vector>
#include <unordered_set>

class Solution {
public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
        std::unordered_set<std::string> words(wordList.begin(), wordList.end());
        if (!words.contains(endWord)) {
            return 0;
        }

        std::queue<std::pair<std::string, int>> word_and_length;
        word_and_length.push({beginWord, 1});
        words.erase(beginWord);

        while (!word_and_length.empty()) {
            auto [word, dist] = word_and_length.front();
            word_and_length.pop();

            if (word == endWord) {
                return dist;
            }

            for (int i = 0; i < word.size(); ++i) {
                char original = word[i];

                for (auto c : "abcdefghijklmnopqrstuvwxyz") {
                    if (c == original) {
                        continue;
                    }

                    word[i] = c;
                    if (words.contains(word)) {
                        word_and_length.push({word, dist + 1});
                        words.erase(word);
                    }
                }
                word[i] = original;
            }
        }
        return 0;
    }
};

```

leetcode上では2-1のほうが2-2より3倍くらい遅い。


### BFSの復習
- **やりたいこと**: グラフの各頂点の始点からの距離を調べるとか、グラフにおいて終点を見つける、個数を数えるとか

- **各頂点でのタスク**
  1. 値を読み取る、比較する、距離を更新するなどもともとの目的
  2. その頂点から次に走査したい頂点をタスクキューに入れる
  3. キューから次の頂点を取り出し1に戻る
