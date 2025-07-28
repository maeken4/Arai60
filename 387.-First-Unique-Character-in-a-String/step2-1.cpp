#include <limits>
#include <map>
#include <ranges>
#include <string>
// map
class Solution {
   public:
    // Return the index of the first character which appears exactly once in the string,
    // or -1 if no such character exists.
    int firstUniqChar(const std::string& s) {
        std::map<char, int> char_to_first_appear_index;
        for (int i = 0; i < s.size(); ++i) {
            if (char_to_first_appear_index.contains(s[i])) {
                char_to_first_appear_index[s[i]] = std::numeric_limits<int>::max();
            } else {
                char_to_first_appear_index[s[i]] = i;
            }
        }
        auto min_value = std::ranges::min(char_to_first_appear_index | std::ranges::views::values);
        if (min_value < std::numeric_limits<int>::max()) {
            return min_value;
        } else {
            return -1;
        }
    }
};
