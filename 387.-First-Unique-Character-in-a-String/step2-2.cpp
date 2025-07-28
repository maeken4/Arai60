#include <list>
#include <map>
#include <set>
#include <string>
// map + list
class Solution {
   public:
    int firstUniqChar(const std::string& s) {
        // iter==seen_once_chars.end()は2度以上現れたことを意味する
        std::map<char, std::list<int>::iterator> char_to_pos_in_candidates;
        std::list<int> seen_once_chars;  // 1度だけ現れた文字のindexを保持
        for (int i = 0; i < s.size(); ++i) {
            auto c = s[i];
            auto map_iter = char_to_pos_in_candidates.find(c);
            if (map_iter == char_to_pos_in_candidates.end()) {
                auto iter = seen_once_chars.insert(seen_once_chars.end(), i);
                char_to_pos_in_candidates[c] = iter;
            } else if (map_iter->second != seen_once_chars.end()) {
                seen_once_chars.erase(map_iter->second);
                map_iter->second = seen_once_chars.end();
            }
        }
        if (seen_once_chars.empty()) {
            return -1;
        }
        return seen_once_chars.front();
    }
};
