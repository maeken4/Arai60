#include <map>
#include <vector>

class Solution {
  public:
    int subarraySum(const std::vector<int>& nums, int k) {
        int result = 0;
        int accumulate = 0;
        std::map<int, int> accumulate_count = {{accumulate, 1}};
        for (const auto& num : nums) {
            accumulate += num;
            result += accumulate_count[accumulate - k];
            accumulate_count[accumulate]++;
        }
        return result;
    }
};
