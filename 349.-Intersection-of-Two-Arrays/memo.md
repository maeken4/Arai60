# step1
- 両方setに変換して、片方を走査してもう片方に入っているかチェックしていく。
- std::setに変換するところ、あるいはチェックするところがボトルネックになり時間計算量O(max(n1*log(n1), n2*log(n2), n2*log(n1)))
- nums1, 2が非対称のとき
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
(https://github.com/ryosuketc/leetcode_arai60/pull/13)
