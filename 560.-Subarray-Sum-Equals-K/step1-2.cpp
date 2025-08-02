#include <map>
#include <vector>

class Solution {
  public:
    int subarraySum(const std::vector<int>& nums, int k) {
        std::map<int, int> imterim_accumulate_count;
        int ans = 0;
        int accumulate = 0;
        for (const auto& num : nums) {
            imterim_accumulate_count[accumulate]++;
            accumulate += num;
            if (imterim_accumulate_count.contains(accumulate - k)) {
                ans += imterim_accumulate_count[accumulate - k];
            }
        }
        return ans;
    }
};
