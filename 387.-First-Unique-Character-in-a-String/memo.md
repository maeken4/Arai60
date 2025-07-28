# step1
先に回数を記録して、次に最初から走査して最初に登場回数が1回の文字を探す。二回文字列を走っているのが何とかなりそうだがいい方法が思いつかなかった。案の定ちょっと遅いようだ。
```cpp
#include <map>
#include <string>

class Solution {
   public:
    // map & 2 pass
    int firstUniqChar(const std::string& s) {
        std::map<char, int> count_appearing_number;
        for (char c : s) {
            count_appearing_number[c]++;
        }
        for (int i = 0; i < s.size(); ++i) {
            if (count_appearing_number[s[i]] == 1) {
                return i;
            }
        }
        return -1;
    }
};

```


# step2
他の人のレビューを読む
https://github.com/colorbox/leetcode/pull/29/files
- 定数はconstexprが好ましい
- .hにメソッドと説明を書くイメージ(https://source.chromium.org/gn/gn/+/main:src/base/files/file.h;l=155?q=%5C%20%5C%20%2F%2F.*-1%20file:.h$)

hayashi-ayさんの一周だけ走査する方法(そのあとminをとってるけど高々文字種分しか要素はない)をC++に翻訳してみる。
https://github.com/hayashi-ay/leetcode/pull/28/files#diff-5ec7c3c87171edf4d61e9eb79fd926cafa27caf068da7474222897c8e9e7ab96R71
Pythonのinfでは適切に他の数との演算が定められているようだが、std::numeric_limitだと後の人が下手にいじってオーバーフローしそうでちょっと怖い気持ちになった。

```cpp:step2-1.cpp
#include <limits>
#include <map>
#include <ranges>
#include <string>

class Solution {
   public:
    // map
    // Return the index of the first character which appears exactly once in the string,
    // or -1 if no such character exists.
    int firstUniqChar(const std::string& s) {
        std::map<char, int> char_to_first_appear_index;
        for (int i = 0; i < s.size(); ++i) {
            if (char_to_first_appear_index.contains(s[i])) {
                char_to_first_appear_index[s[i]] = std::numeric_limits<int>::max();
            } else {
                char_to_first_appear_index[s[i]] = i;
            }
        }
        auto min_value = std::ranges::min(char_to_first_appear_index | std::ranges::views::values);
        if (min_value < std::numeric_limits<int>::max()) {
            return min_value;
        } else {
            return -1;
        }
    }
};

```

上とほぼ同様だがnumeric_limtsを使わないようにした。結局mapのvalueから-1を除いてminを求めるところがすっきり書けない…
```cpp:step2-1-2.cpp
#include <algorithm>
#include <map>
#include <ranges>
#include <string>
// map
class Solution {
   public:
    // Return the index of the first character which appears exactly once in the string,
    // or -1 if no such character exists.
    int firstUniqChar(const std::string& s) {
        // set to -1 after the character is seen twice.
        std::map<char, int> char_to_first_appear_index;
        for (int i = 0; i < s.size(); ++i) {
            if (char_to_first_appear_index.contains(s[i])) {
                char_to_first_appear_index[s[i]] = -1;
            } else {
                char_to_first_appear_index[s[i]] = i;
            }
        }
        auto view = char_to_first_appear_index | std::views::filter([](const auto& p) { return p.second != -1; });
        auto it = std::ranges::min_element(view, {}, [](const auto& p) { return p.second; });
        return it != view.end() ? it->second : -1;
    }
};

```

## step2-2
LinkedHashMapっぽいなにか。一瞬、挿入・アクセス・削除がO(1)でできるlistの上位互換を作った気もしたが同じ要素が二度入らないようにしてあった。(つまりLinkedHashSet)
```cpp:step2-2.cpp
#include <list>
#include <map>
#include <set>
#include <string>
// map + list
class Solution {
   public:
    int firstUniqChar(const std::string& s) {
        // iter==seen_once_chars.end()は2度以上現れたことを意味する
        std::map<char, std::list<int>::iterator> char_to_pos_in_candidates;
        std::list<int> seen_once_chars;  // 1度だけ現れた文字のindexを保持
        for (int i = 0; i < s.size(); ++i) {
            auto c = s[i];
            auto map_iter = char_to_pos_in_candidates.find(c);
            if (map_iter == char_to_pos_in_candidates.end()) {
                auto iter = seen_once_chars.insert(seen_once_chars.end(), i);
                char_to_pos_in_candidates[c] = iter;
            } else if (map_iter->second != seen_once_chars.end()) {
                seen_once_chars.erase(map_iter->second);
                map_iter->second = seen_once_chars.end();
            }
        }
        if (seen_once_chars.empty()) {
            return -1;
        }
        return seen_once_chars.front();
    }
};

```


set+mapを使った解法。1パスで簡潔に書ける。
https://github.com/quinn-sasha/leetcode/pull/15/files?short_path=5ec7c3c#diff-5ec7c3c87171edf4d61e9eb79fd926cafa27caf068da7474222897c8e9e7ab96
```cpp:step2-3.cpp
#include <algorithm>
#include <map>
#include <set>
#include <string>
// set + map
class Solution {
   public:
    int firstUniqChar(const std::string& s) {
        std::set<char> repeated_chars;
        std::map<char, int> candidate_char_to_index;
        for (int i = 0; i < s.size(); i++) {
            auto c = s[i];
            if (repeated_chars.contains(c)) {
                continue;
            }
            if (candidate_char_to_index.contains(c)) {
                candidate_char_to_index.erase(c);
                repeated_chars.insert(c);
                continue;
            }
            candidate_char_to_index[c] = i;
        }
        if (candidate_char_to_index.empty()) {
            return -1;
        } else {
            auto cmp = [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; };
            auto it = std::min_element(candidate_char_to_index.begin(), candidate_char_to_index.end(), cmp);
            return it->second;
        }
    }
};

```

# step3
```cpp:step3.cpp
#include <algorithm>
#include <map>
#include <set>
#include <string>

class Solution {
   public:
    int firstUniqChar(const std::string& s) {
        std::set<char> repeated_chars;
        std::map<char, int> candidate_char_to_index;
        for (int i = 0; i < s.size(); ++i) {
            auto c = s[i];
            if (repeated_chars.contains(c)) {
                continue;
            } else if (candidate_char_to_index.contains(c)) {
                candidate_char_to_index.erase(c);
                repeated_chars.insert(c);
                continue;
            }
            candidate_char_to_index[c] = i;
        }
        if (candidate_char_to_index.empty()) {
            return -1;
        }
        auto cmp = [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; };
        auto it = std::min_element(candidate_char_to_index.begin(), candidate_char_to_index.end(), cmp);
        return it->second;
    }
};

```
