# step1
- 両方setに変換して、片方を走査してもう片方に入っているかチェックしていく。
- std::setに変換するところ、あるいはチェックするところがボトルネックになり時間計算量O(max(n1*log(n1), n2*log(n2), n2*log(n1)))
- nums2.size() < nums1.size()ならばよいが、入力に応じて逆にしたほうがよい。
```cpp
#include <set>
#include <vector>

class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::set nums1_set(nums1.begin(), nums1.end());
    std::set nums2_set(nums2.begin(), nums2.end());
    std::vector<int> result;

    for (const auto num : nums2_set) {
        if (nums1_set.contains(num)) {
            result.push_back(num);
        }
    }

    return result;
    }
};
```

# step2
STLにstd::set_intersectionとかいういかにも使えそうなやつがあったが、入力の両者がソートされていることが前提なうえ、多重集合としてカウントしてしまうためちょっとめんどくさかった。
```cpp
#include <algorithm>
#include <iterator>
#include <vector>


class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::vector<int> result;
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());

    std::set_intersection(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), std::back_inserter(result));
    result.erase(std::unique(result.begin(), result.end()), result.end())

    return result;
    }
};

```

## 他の方のレビュー
https://github.com/ryosuketc/leetcode_arai60/pull/13

https://github.com/quinn-sasha/leetcode/pull/13#discussion_r1960884543


## マージソート復習
### マージのアルゴリズム
背の順になっている二つのクラスA、Bがあるとして、二つを合わせた背の順を作りたい。
先頭の人の伸長同士を比べて、小さいほうをマージクラスに入れて先頭の人を更新していけばよい。比較は合計len(A)+len(B)回

### マージソート
配列を長さ1の区間に分割して、下から順々にマージ&ソートしていけばよい。


ChatGPTに書いてもらったものを理解しやすい形にしたもの
```cpp:merge_sort.cpp
#include <iostream>
#include <iterator>
#include <vector>

// 自前のマージ関数
template <typename RandomIt, typename Compare>
void merge(RandomIt first, RandomIt mid, RandomIt last, Compare comp) {
    using ValueType = std::iter_value_t<RandomIt>;  // C++20
    // using ValueType = typename std::iterator_traits<RandomIt>::value_type;
    std::vector<ValueType> buffer;
    buffer.reserve(std::distance(first, last));

    RandomIt left = first;
    RandomIt right = mid;
    // どちらかに要素がある限りループ
    while (left != mid || right != last) {
        if (left == mid) {
            // 左がなければ右だけを吸い出す
            buffer.push_back(*right++);  // 後置インクリメントなので評価されてから++
        } else if (right == last) {
            // 右がなければ左だけを吸い出す
            buffer.push_back(*left++);
        } else if (comp(*left, *right)) {
            buffer.push_back(*left++);
        } else {
            buffer.push_back(*right++);
        }
    }
    // 元の範囲に書き戻す
    std::copy(buffer.begin(), buffer.end(), first);
}

// 再帰的なマージソート本体（比較関数あり）
template <typename RandomIt, typename Compare>
void merge_sort(RandomIt first, RandomIt last, Compare comp) {
    auto n = std::distance(first, last);
    if (n < 2) return;  // 要素数0または1ならソート不要

    RandomIt mid = first;
    std::advance(mid, n / 2);

    merge_sort(first, mid, comp);
    merge_sort(mid, last, comp);
    merge(first, mid, last, comp);
}

// デフォルト比較（operator<）を使うオーバーロード
template <typename RandomIt>
void merge_sort(RandomIt first, RandomIt last) {
    using ValueType = std::iter_value_t<RandomIt>;  // C++20
    // using ValueType = typename std::iterator_traits<RandomIt>::value_type;
    merge_sort(first, last, std::less<ValueType>{});
}

int main() {
    std::vector<int> v = {324, 32, 33, 22, 1, 1, 3};
    merge_sort(v.begin(), v.end());
    for (auto x : v) {
        std::cout << x << std::endl;
    }
}

```



### マージのアルゴリズムを流用した元の問題の解法
https://discord.com/channels/1084280443945353267/1183683738635346001/1190255718876585994

理解しやすかったのでそのまま写した。ソートがボトルネック。
```cpp
#include <ranges>
#include <vector>

class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::ranges::sort(nums1);
        std::ranges::sort(nums2);
        std::vector<int> result;
        auto pointer1 = nums1.begin();
        auto pointer2 = nums2.begin();
        while (pointer1 != nums1.end() && pointer2 != nums2.end()) {
            if (*pointer1 < *pointer2) {
                ++pointer1;
                continue;
            }
            if (*pointer2 < *pointer1) {
                ++pointer2;
                continue;
            }
            int common = *pointer1;
            result.push_back(common);
            while (pointer1 != nums1.end() && *pointer1 == common) {
                ++pointer1; 
            }
            while (pointer2 != nums2.end() && *pointer2 == common) {
                ++pointer2;
            }
        }

        return result;
    }
};

```


# step3
```cpp
#include <ranges>
#include <vector>

class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::ranges::sort(nums1);
        std::ranges::sort(nums2);
        std::vector<int> result;

        auto pointer1 = nums1.begin();
        auto pointer2 = nums2.begin();
        while (pointer1 != nums1.end() && pointer2 != nums2.end()) {
            if (*pointer1 < *pointer2) {
                ++pointer1;
                continue;
            }
            if (*pointer2 < *pointer1) {
                ++pointer2;
                continue;
            }

            int common = *pointer1;
            result.push_back(common);
            while(pointer1 != nums1.end() && *pointer1 == common) {
                ++pointer1;
            }
            while(pointer2 != nums2.end() && *pointer2 == common) {
                ++pointer2;
            }
        }
        return result;
    }
};

```

# step3-2
nodchipさんのコメントを踏まえて修正
```cpp
#include <iterator>
#include <ranges>
#include <set>
#include <vector>

class Solution {
public:
    std::vector<int> intersection(const std::vector<int>& nums1, const std::vector<int>& nums2) {
        auto unique_nums1 = nums1 | std::ranges::to<std::set>();
        auto unique_nums2 = nums2 | std::ranges::to<std::set>();
        std::vector<int> result;
        std::ranges::set_intersection(unique_nums1, unique_nums2, std::back_inserter(result));
        return result;
    }
};

```
