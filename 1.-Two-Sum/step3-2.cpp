#include <set>
#include <vector>

class Solution {
   public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        auto comp = [](const auto a, const auto b) { return a.frist < b.first; };
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
