# step1
- 愚直にやると二重ループだが何度も同じ値を参照することになり無駄が多い(時間計算量O(n^2))
- 小さい順に並べておくと、一つ固定した下で対となりうる値はそれより後ろにしかなく二分探索で見つけられる。
- 似たような問題設定をatcoderの典型の練習でやったことがあった。が、lower_boundの使い方などに手間取り時間がかかってしまった。
```cpp
#include <vector>

class Solution {
   public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<std::pair<int, int>> nums_with_index;
        for (int i = 0; i < nums.size(); ++i) {
            nums_with_index.push_back(std::make_pair(nums[i], i));
        }
        std::sort(nums_with_index.begin(), nums_with_index.end());

        for (int i = 0; i < nums_with_index.size(); ++i) {
            auto compare_num = [](const auto& a, const auto& b) { return a.first < b.first; };
            // numの比較しかしないのでindexはdummy
            const auto complement = std::make_pair(target - nums_with_index[i].first, -1);
            auto it = std::lower_bound(nums_with_index.begin() + i + 1, nums_with_index.end(), complement, compare_num);
            if (it != nums_with_index.end() && (*it).first == complement.first) {
                return std::vector<int>{nums_with_index[i].second, (*it).second};
            }
        }
        // 入力が正しければ到達しない
        return std::vector<int>{0, 0};
    }
};

```

# step2
[omotiさんの解法](https://discord.com/channels/1084280443945353267/1218823752243089408/1239215124477378580)でもやってみる。


自分の持ったイメージ。
1. 例：[1, 2, 3, 3, 4, 8, 8, 12, 14, 13]からX+Y=Tとなるペアを探す。
2. (X+Y)/2=T/2と言い換えてみると、数直線上に有限個の点が並んでいて、二つ選んで平均がぴったりT/2になるようにしたいと言い換えられる。
3. 平均をとってみて所望の数より小さければ左を大きくすればいいし、大きければ右を小さくすればよい

```cpp

#include <vector>

class Solution {
   public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<std::pair<int, int>> nums_with_index;
        for (int i = 0; i < nums.size(); ++i) {
            nums_with_index.push_back(std::make_pair(nums[i], i));
        }
        std::sort(nums_with_index.begin(), nums_with_index.end());

        int left = 0;
        int right = nums_with_index.size() - 1;
        while (nums_with_index[left].first + nums_with_index[right].first != target) {
            if (nums_with_index[left].first + nums_with_index[right].first < target) {
                left++;
            }
            else {
                right--;
            }
        }
        return {nums_with_index[left].second, nums_with_index[right].second};
    }
};

```

# step3
本質的に変わらないけどイテレーターで書き直した。
```cpp
#include <vector>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<std::pair<int, int>> nums_with_indices;
        for (auto it = nums.begin(); it != nums.end(); it++) {
            nums_with_indices.push_back(std::make_pair(*it, it - nums.begin()));
        }
        std::sort(nums_with_indices.begin(), nums_with_indices.end());
        auto left = nums_with_indices.begin();
        auto right = nums_with_indices.end() - 1;
        while ((*left).first + (*right).first != target) {
            if ((*left).first + (*right).first < target) {
                left++;
            }
            else {
                right--;
            }
        }
        return {(*left).second, (*right).second};
    }
};

```


## ryosuketcさんのコメント
numsを走査し見つけた数をsetに入れていく。入れるまえに対応する数がすでに入っていればそこで終了できるため場合によっては早いし、最悪でもO(nlogn)で他の解法と変わらない
- setを使った解法
```cpp
#include <set>
#include <vector>

class Solution {
   public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        auto comp = [](const auto a, const auto b) { return a.first < b.first; };
        std::set<std::pair<int, int>, decltype(comp)> seen_num_or_complement_with_index(comp);
        std::vector<int> two_indices;

        for (auto it = nums.begin(); it != nums.end(); ++it) {
            int DUMMY = -1;
            const auto complement = seen_num_or_complement_with_index.find(std::make_pair(target - *it, DUMMY));
            if (complement != seen_num_or_complement_with_index.end()) {
                two_indices = {int(it - nums.begin()), (*complement).second};
            } else {
                seen_num_or_complement_with_index.insert(std::make_pair(*it, it - nums.begin()));
            }
        }

        return two_indices;
    }
};

```
- 解答を見直したところmapのほうがずっとすっきりかける
```cpp
#include <map>
#include <vector>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> seen_num_to_index;
        std::vector<int> two_indices;

        for (int i = 0; i < nums.size(); ++i) {
            auto complement = seen_num_to_index.find(target - nums[i]);
            if (complement != seen_num_to_index.end()) {
                two_indices = {i, complement->second};
                break;
            }
            else {
                seen_num_to_index[nums[i]] = i;
            }
        }

        return two_indices;
    }
};

```
