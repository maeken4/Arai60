# step1
- スタックのセクションにあったのでとりあえずスタックで解いた。
- 素直に書いてガチャガチャ変えて動いてしまった。よくない。
```cpp:step1.cpp
#include <stack>

class Solution {
   public:
    ListNode* reverseList(ListNode* head) {
        std::stack<ListNode*> st;
        ListNode* tail = head;
        // nullをはじくのを統一的に書けないか？
        if (head == nullptr) {
            return nullptr;
        }
        while(tail != nullptr) {
            st.push(tail);
            tail = tail->next;
        }
        head = st.top();
        st.pop();
        tail = head;
        while(!st.empty()) {
            tail->next = st.top();
            st.pop();
            tail = tail->next;
        }
        // これってなんで必要？
        tail->next = nullptr;
        return head;
    }
};

```

# step2
- 再帰で書けることに気づく。
```cpp:step2.cpp
class Solution {
   public:
    ListNode* reverseList(ListNode* head) {
        return reverseRecursively(head);
    }
   private:
    // node以降のリストを逆順に繋ぎなおし、元々の最後尾を新たなheadとして返す
    ListNode* reverseRecursively(ListNode* node) {
        if (node == nullptr || node->next == nullptr) {
            return node;
        }
        ListNode* head =  reverseRecursively(node->next);
        node->next->next = node;
        node->next = nullptr;
        return head;
    }
};
```
人のコードを見る。
- step1ですっきりしなかった部分も番兵を使うときれいに書ける([linoahhhさん](https://github.com/lilnoahhh/leetcode/pull/10/files/31a6eddb4e971614db2b6d2fb67da1a44fb764c4#r1948006046))。
- スタックに入っているノードを取り出してつなげる、というのに最後の場合分けが生じなくてよくなる。
```cpp
#include <stack>

class Solution {
   public:
    ListNode* reverseList(ListNode* head) {
        std::stack<ListNode*> st;
        ListNode* sentinel = nullptr;
        st.push(sentinel);
        ListNode* tail = head;
        while (tail) {
            st.push(tail);
            tail = tail->next;
        }

        ListNode* new_head = st.top();st.pop();
        tail = new_head;
        while (!st.empty()) {
            tail->next = st.top();
            st.pop();
            tail = tail->next;
        }
        return head;
    }
};
```


- もっと素直に前後を入れ替えていく([tarinaihitoriさん](https://discord.com/channels/1084280443945353267/1295357747545505833/1298524551592018003))
```cpp:step2_another.cpp
class Solution {
   public:
    ListNode* reverseList(ListNode* head){
        // 反転済みリストの先頭
        ListNode* reversed_head = nullptr;
        ListNode* cur_node = head;
        while (cur_node) {
            ListNode* tmp = cur_node->next;
            tail->next = reversed_head;
            reversed_head = cur_node;
            cur_node = tmp;
        }
        return reversed_head;
    }
};
```

シンプルな問だけどけっこう方針が違う解法があって面白い。


# step3
スタック
```cpp:step3.cpp
#include <stack>
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        std::stack<ListNode*> st;
        auto sentinel = nullptr;
        st.push(sentinel);
        auto tail = head;
        while (tail) {
            st.push(tail);
            tail = tail->next;
        }

        auto new_head = st.top();
        st.pop();
        tail = new_head;
        while (tail) {
            tail->next = st.top();
            st.pop();
            tail = tail->next;
        }
        return new_head;
    }
};
```

シンプルな交換
```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* reversed_head = nullptr;
        ListNode* cur_node = head;
        while (cur_node) {
            auto tmp = cur_node->next;
            cur_node->next = reversed_head;
            reversed_head = cur_node;
            cur_node = tmp;
        }
        return reversed_head;
    }
};
```
