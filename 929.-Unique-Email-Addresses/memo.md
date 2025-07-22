# step1
愚直に@の手前までは"."を無視して"+"が出現したら後は入れないとし、@発見後はそのままコピーし構築する方法。

他にあるとしたら正規表現とか？
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
            result.insert(std::move(normalized_email));
        }
        return result.size();
    }
};
```

# step2
STLの文字列の機能を使った実装
```cpp
#include <algorithm>
#include <set>
#include <vector>

class Solution {
   public:
    int numUniqueEmails(std::vector<std::string>& emails) {
        std::set<std::string> seen;
        for (const auto& email : emails) {
            seen.insert(std::move(normalize_email(email)));
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
        // C++20以降ではstd::erase(local, '.');でも可
        local.erase(std::remove(local.begin(), local.end(), '.'), local.end());
        return local + at_domain;
    }
};

```
あるいはをやや不自然な感じもするがrangesを使った実装
```cpp
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
            seen.insert(std::move(processed_email));
        }
        return seen.size();
    }
};

```

## 他の人のPRを読む
- https://github.com/shintaroyoshida20/leetcode/tree/feature/hash-map/unique-email-addresses
ちゃんと入力が正しいことをチェックすると大変そう。RFCは気になったときに目を通したい…
異常系も考慮するなら、ユーザーの入力のバリデーションの場面なら例外を投げてやり直させる/データ処理の場面なら不適データは無視する、といった形にする気がする。
- 整理できていなかったが、Pythonではstr1+=cとしたときに元の文字列の再構築が起きるためループで順次足すのはまずいが、C++では問題ない。https://github.com/Ryotaro25/leetcode_first60/pull/15/files#r1641792391
>C++ は、文字列は mutable なので特に問題はないです。Java、Python は immutable です。
ちなみに、こういうのはよく知らない言語を触るときに一番初めに確認することの一つです。


# step3
```cpp
#include <set>
#include <string>
#include <vector>

class Solution {
public:
    int numUniqueEmails(const std::vector<std::string>& emails) {
        std::set<std::string> seen;
        for (const auto& email : emails) {
            seen.insert(std::move(normalized_email(email)));
        }
        return seen.size();
    }
private:
    std::string normalized_email(const std::string& email) {
        auto at_position = email.find('@');
        auto local = email.substr(0, at_position);
        auto at_domain = email.substr(at_position);
        if (auto plus_position = local.find('+'); plus_position != std::string::npos) {
            local.resize(plus_position);
        }
        std::erase(local, '.');
        return  local + at_domain;
    }
};
```

