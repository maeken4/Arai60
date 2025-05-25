#include <map>
#include <string>

class Solution {
   public:
    bool isValid(std::string s) {
        std::map<std::string, int> counter;
        for (const auto& c : s) {
            switch (c) {
                case '(':
                    counter["round"]--;
                    if (counter["round"] > 0) {
                        return false;
                    }
                    break;
                case ')':
                    counter["round"]++;
                    if (counter["round"] > 0) {
                        return false;
                    }
                    break;
                case '{':
                    counter["curly"]--;
                    if (counter["curly"] > 0) {
                        return false;
                    }
                    break;
                case '}':
                    counter["curly"]++;
                    if (counter["curly"] > 0) {
                        return false;
                    }
                    break;
                case '[':
                    counter["square"]--;
                    if (counter["square"] > 0) {
                        return false;
                    }
                    break;
                case ']':
                    counter["square"]++;
                    if (counter["square"] > 0) {
                        return false;
                    }
                    break;
            }
        }
        if (counter["round"] != 0 || counter["curly"] != 0 || counter["square"] != 0) {
            return false;
        }
        return true;
    }
};
