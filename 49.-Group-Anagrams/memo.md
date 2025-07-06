# step1
- 各文字列は辞書順を基準とすることでアナグラムかどうか判定する。
- "ant" -> {"nat", "tan"}みたいなmapを持たせればよさそう。
```cpp
#include <algorithm>
#include <map>
#include <ranges>
#include <string>
#include <vector>

class Solution {
   public:
    std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
        std::map<std::string, std::vector<std::string>> dictionary_order_to_anagrams;
        for (auto& str : strs) {
            std::string sorted = str;
            std::sort(sorted.begin(), sorted.end());
            dictionary_order_to_anagrams[sorted].push_back(str);
        }

        std::vector<std::vector<std::string>> result;
        for (const auto& [_, group] : dictionary_order_to_anagrams) {
            result.push_back(group);
        }
        return result;
    }
};

```


# step2
- C++23の機能を使うとコンテナの変換が簡単に書けることが調べたらわかった。
- 計算量をちゃんと考えていなかったが、各文字列のサイズ(の最大)をm、文字列の個数をnとしてO(n*m*logm).
- mapをunordered_mapに変えた。今まであまり意識できていなかったが、要素の(キーに関する)順序が必要ない場合はunordered_mapのほうがよさそう。
```cpp
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <string>
#include <vector>

class Solution {
   public:
    std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> dictionary_order_to_anagrams;
        for (auto& str : strs) {
            std::string sorted = str;
            std::sort(sorted.begin(), sorted.end());
            dictionary_order_to_anagrams[sorted].push_back(str);
        }
        return dictionary_order_to_anagrams | std::views::values | std::ranges::to<std::vector>();
    }
};

```

- 各文字列に出現するアルファベットをカウントする方法。
- 先の解法と違ってアルファベット以外を想定に入れると文字の種類だけのメモリを常に使用することになる。
- unordered_mapをvector<int>に対して使うにはハッシュ関数を書かないといけないみたいなので、mapで書いた。
```cpp
#include <ranges>
#include <vector>

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
        std::map<std::vector<int>, std::vector<std::string>> counter_to_anagrams;
        for (const auto& str : strs) {
            counter_to_anagrams[count_alphabet(str)].push_back(str);
        }
        return counter_to_anagrams | std::views::values | std::ranges::to<std::vector>();
    }
private:
    std::vector<int> count_alphabet(const std::string& str) {
        std::vector<int> counter(26);
        for (const char c : str) {
            counter[c - 'a']++;
        }
        return counter;
    }
};

```

# step3
ソートする方法。5分程度で三回
```cpp
#include <algorithm>
#include <ranges>
#include <unordered_map>
#include <vector>

class Solution {
   public:
    std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> dictionary_order_to_anagrams;
        for (const auto& str : strs) {
            auto key = str;
            std::sort(key.begin(), key.end());
            dictionary_order_to_anagrams[key].push_back(str);
        }
        return dictionary_order_to_anagrams | std::views::values | std::ranges::to<std::vector>();
    }
};

```

rangeの練習
```cpp
#include <iostream>
#include <optional>
#include <ranges>
#include <vector>

int main() {
    std::vector<std::optional<int>> ov = {1, std::nullopt, 3};
    auto present = ov | std::views::filter([](auto &o) { return o.has_value(); }) |
                   std::views::transform([](auto &o) { return *o; });
    for (int x : present) std::cout << x << ' ';

    auto view1 = std::views::iota(0, 100)                                // [0,100)
                 | std::views::filter([](int x) { return x % 2 == 0; })  // 2で割り切れるものだけ取り出す
                 | std::views::transform([](int x) { return x * 2; })    // すべて2倍
                 | std::views::take_while([](int x) { return x < 20; });
}
```

