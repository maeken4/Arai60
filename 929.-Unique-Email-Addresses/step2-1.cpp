#include <algorithm>
#include <set>
#include <string>
#include <vector>

class Solution {
   public:
    int numUniqueEmails(std::vector<std::string>& emails) {
        std::set<std::string> seen;
        for (const auto& email : emails) {
            seen.insert(normalize_email(email));
        }
        return seen.size();
    }

   private:
    std::string normalize_email(const std::string& email) {
        auto at_position = email.find('@');
        auto local = email.substr(0, at_position);
        auto at_domain = email.substr(at_position);
        if (auto plus_position = local.find('+'); plus_position != std::string::npos) {
            local.resize(plus_position);
        }
        local.erase(std::remove(local.begin(), local.end(), '.'), local.end());

        return local + at_domain;
    }
};
