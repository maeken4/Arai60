#include <map>
#include <string>

class Solution {
   public:
    int firstUniqChar(const std::string& s) {
        std::map<char, int> count_appearing_number;
        for (char c : s) {
            count_appearing_number[c]++;
        }
        for (int i = 0; i < s.size(); ++i) {
            if (count_appearing_number[s[i]] == 1) {
                return i;
            }
        }
        return -1;
    }
};
