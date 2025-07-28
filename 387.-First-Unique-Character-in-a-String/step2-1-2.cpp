#include <algorithm>
#include <map>
#include <ranges>
#include <string>
// map
class Solution {
   public:
    // Return the index of the first character which appears exactly once in the string,
    // or -1 if no such character exists.
    int firstUniqChar(const std::string& s) {
        // set to -1 after the character is seen twice.
        std::map<char, int> char_to_first_appear_index;
        for (int i = 0; i < s.size(); ++i) {
            if (char_to_first_appear_index.contains(s[i])) {
                char_to_first_appear_index[s[i]] = -1;
            } else {
                char_to_first_appear_index[s[i]] = i;
            }
        }
        auto view = char_to_first_appear_index | std::views::filter([](const auto& p) { return p.second != -1; });
        auto it = std::ranges::min_element(view, {}, [](const auto& p) { return p.second; });
        return it != view.end() ? it->second : -1;
    }
};
