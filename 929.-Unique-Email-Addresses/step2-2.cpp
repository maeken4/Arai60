#include <ranges>
#include <set>
#include <vector>

class Solution {
   public:
    int numUniqueEmails(std::vector<std::string>& emails) {
        std::set<std::string> seen;
        for (const auto& email : emails) {
            auto name_ranges = email | std::views::split('@');
            auto it = name_ranges.begin();
            auto local_range = *it;
            auto domain_range = *(++it);
            auto filtered_local_range = local_range | std::views::take_while([](const auto c) { return c != '+'; }) |
                                        std::views::filter([](const auto c) { return c != '.'; });
            std::string processed_email = std::ranges::to<std::string>(filtered_local_range);
            processed_email += '@';
            processed_email += std::ranges::to<std::string>(domain_range);
            seen.insert(processed_email);
        }
        return seen.size();
    }
};
