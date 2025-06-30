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
