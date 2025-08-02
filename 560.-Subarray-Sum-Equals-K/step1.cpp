#include <vector>

class Solution {
  public:
    int subarraySum(const std::vector<int>& nums, int k) {
        std::vector<int> accumulate_list(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); ++i) {
            accumulate_list[i + 1] = accumulate_list[i] + nums[i];
        }
        int ans = 0;
        for (int i = 0; i < accumulate_list.size() - 1; ++i) {
            for (int j = i + 1; j < accumulate_list.size(); ++j) {
                if (accumulate_list[j] - accumulate_list[i] == k) {
                    ++ans;
                }
            }
        }
        return ans;
    }
};
