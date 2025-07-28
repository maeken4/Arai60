#include <algorithm>
#include <map>
#include <set>
#include <string>

class Solution {
   public:
    int firstUniqChar(const std::string& s) {
        std::set<char> repeated_chars;
        std::map<char, int> candidate_char_to_index;
        for (int i = 0; i < s.size(); ++i) {
            auto c = s[i];
            if (repeated_chars.contains(c)) {
                continue;
            } else if (candidate_char_to_index.contains(c)) {
                candidate_char_to_index.erase(c);
                repeated_chars.insert(c);
                continue;
            }
            candidate_char_to_index[c] = i;
        }
        if (candidate_char_to_index.empty()) {
            return -1;
        }
        auto cmp = [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; };
        auto it = std::min_element(candidate_char_to_index.begin(), candidate_char_to_index.end(), cmp);
        return it->second;
    }
};
