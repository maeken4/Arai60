#include <map>
#include <stack>
#include <string>
class Solution {
   public:
    bool isValid(std::string& s) {
        std::map<char, char> open_to_close = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
        std::stack<char> st;
        for (const auto& c : s) {
            // 開き括弧の場合対応する括弧をスタックに置く
            if (open_to_close.contains(c)) {
                st.push(open_to_close[c]);
                // 不適合な場合そこで終了
            } else if (st.empty() || st.top() != c) {
                return false;
                // 適合している場合括弧の組を取り除く
            } else {
                st.pop();
            }
        }
        // 最終的に括弧の組が全部打ち消しあってくれているか
        return st.empty();
    }
};
