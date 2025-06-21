# step1
- 素直に辞書で回数を記録して頻度順に並べた。
  - ソートがボトルネックになって計算量 O(nlogn)
- 数字の書いてあるボールがいっぱいあったら、まず数字ごとにまとめて個数を数えて、個数が大きい順に並べるイメージ。

### 書きながら調べたこと
- std::map<K,V> について、キーが存在しないときにアクセスした場合Vのデフォルトコンストラクタが呼ばれる->intだったら0
- 
```cpp
#include <algorithm>
#include <map>
#include <vector>
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        std::map<int, int> frequency_map;
        for (const auto& num : nums) {
            frequency_map[num]++;
        }
        std::vector<std::pair<int,int>> frequency_list(frequency_map.begin(), frequency_map.end());
        auto comparator = [](std::pair<int, int>& a, std::pair<int, int>& b) {
            return a.second > b.second;
        };
        sort(frequency_list.begin(), frequency_list.end(), comparator);
        
        vector<int> top_k_frequent;
        for (int i = 0; i < k; ++i) {
            top_k_frequent.push_back(frequency_list[i].first);
        }

        return top_k_frequent;
    }
};
```

# step2
- [tarinaihitoriさんへのコメント](https://github.com/tarinaihitori/leetcode/pull/9/files#r1816996368)の観点が抜けていた。step1の書き方だとk種類ないときに配列外エラーが起きる。今回の設定では起こらないので実装は省略するが、実務的には例外を投げるかある分だけ返すと思う。

Pythonだと簡潔に書ける。 [odaさんのコメント](https://github.com/katataku/leetcode/pull/9/files#r1860305454)
```python
from collections import Counter
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        frequency_count = Counter(nums)
        sorted_frequency_count = sorted(frequency_count, key=frequency_count.get, reverse=True)
        return sorted_frequency_count[:k]
```

C++のSTLにnth_element(平均計算量O(n))というのがあるらしい
```cpp
#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution {
public:
    std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
        std::unordered_map<int, int> freq;
        for (int n : nums)　{ freq[n]++; }

        std::vector<int> keys;
        for (auto& [num, _] : freq) { keys.push_back(num); }
        auto cmp = [&](int a, int b) { return freq[a] > freq[b]; };
        // 頻度の上位 k 個を前方に持ってくる
        std::nth_element(keys.begin(), keys.begin() + k, keys.end(), cmp);
        keys.resize(k);

        return keys;
    }
};
```


# step3
変数名を少し工夫。
```cpp
#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        std::unordered_map<int, int> frequency_map;
        for (const auto& num : nums) {
            frequency_map[num]++;
        }
        std::vector<int> keys;
        for (const auto& [num, _] : frequency_map) {
            keys.push_back(num);
        }
        auto compare_frequency = [&](int a, int b) { return frequency_map[a] > frequency_map[b]; };
        std::nth_element(keys.begin(), keys.begin() + k, keys.end(), compare_frequency);
        keys.resize(k);
        return keys;
    }
};
```
