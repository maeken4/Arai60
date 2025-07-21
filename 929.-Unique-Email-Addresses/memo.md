# step1
愚直に@の手前までは"."を無視して"+"が出現したら後は入れないとした。他にあるとしたら正規表現とか？
```cpp
#include <set>
#include <vector>

class Solution {
public:
    int numUniqueEmails(std::vector<std::string>& emails) {
        std::set<std::string> result;
        for (const auto& email : emails) {
            std::string normalized_email;

            auto it = email.begin();
            bool findplus = false;
            while (*it != '@') {
                if (findplus) {
                    ++it;
                    continue;
                }
                if (*it == '.') {
                    ++it;
                    continue;
                }
                if (*it == '+') {
                    findplus = true;
                    ++it;
                    continue;
                }
                normalized_email.push_back(*it);
                ++it;
            }

            while (it != email.end()) {
                normalized_email.push_back(*it);
                ++it;
            }
            result.insert(normalized_email);
        }
        return result.size();
    }
};
```
