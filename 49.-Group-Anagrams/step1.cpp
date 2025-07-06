#include <algorithm>
#include <map>
#include <ranges>
#include <string>
#include <vector>

class Solution {
   public:
    std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
        std::map<std::string, std::vector<std::string>> dictionary_order_to_anagrams;
        for (auto& str : strs) {
            std::string sorted = str;
            std::sort(sorted.begin(), sorted.end());
            dictionary_order_to_anagrams[sorted].push_back(str);
        }

        std::vector<std::vector<std::string>> result;
        for (const auto& [_, group] : dictionary_order_to_anagrams) {
            result.push_back(group);
        }
        return result;
    }
};
