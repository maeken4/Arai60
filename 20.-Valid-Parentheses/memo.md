# step1
- 問題文を正しく理解できていなかった。途中の時点で個数が対応しているだけでは不十分。
- atcoder系で見た一種類の括弧の場合の判定と多分混同してちゃんとシミュレーションせずに書き始めてしまった…
- ( [ ) ]とかでだめになる
```cpp:step1_wrong.cpp
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

```

# step2
- 正しい条件は、
    1. 各種類の括弧について、文字列の任意の位置で開き括弧<=閉じ括弧
    2. 各種類の括弧について、最終的に開き括弧=閉じ括弧
    
    1,2で括弧の対応が決まり、その上で、
    
    3. **閉じ括弧は文字列中で“最後に開かれた未対応の開き括弧”と必ず対応する。**
- 理論的にはスタックで書けることがすぐわかるらしい？
- chatGPTに聞いた文脈自由文法の定義
  1. S → SS          （連接）
  2. S → "(" S ")"   （丸括弧で囲む）
  3. S → "[" S "]"   （角括弧で囲む）
  4. S → "{" S "}"   （波括弧で囲む）
  5. S → ε           （空列）

        を考えるとたしかにスタックで対応付けていくの自然な気がしてくる。
```cpp:step2.cpp
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

```

# step3
試しにマークダウンだけで書いてみたけどちょこちょこメソッド名とか出てこない…ってなる。言語にある程度なれたら補完なしで練習してみてもいいかも
```cpp:step3.cpp
#include <map>
#include <stack>
#include <string>

class Solution {
   public:
    bool isValid(std::string& s) {
        std::map<char,char> open_to_close = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
        std::stack<char> st;
        for (const auto& c : s) {
            if(open_to_close.contains(c)) {
                st.push(open_to_close[c]);
            } else if (st.empty() || st.top() != c) {
                return false;
            } else {
                st.pop();
            }
        }
        return st.empty();
    }
};
```
