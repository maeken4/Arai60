#include <stack>
#include <string>

class Solution {
   public:
    bool isValid(const std::string& s) {
        std::stack<char> st;
        for (const auto& c : s) {
            // 閉じ括弧だけ来るのは不適
            if ((st.empty() || !isPair(st.top(), c)) && (c == ')' || c == '}' || c == ']')) {
                return false;
            }

            if (!st.empty() && isPair(st.top(), c)) {
                st.pop();
            } else {
                st.push(c);
            }
        }
        // 括弧が閉じられていない場合スタックに残っている
        return st.empty();
    }

   private:
    bool isPair(char r, char l) { return (r == '(' && l == ')' || (r == '{' && l == '}') || (r == '[' && l == ']')); }
};
