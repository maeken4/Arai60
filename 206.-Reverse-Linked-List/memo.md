# step1
素直に書いてガチャガチャ変えて動いてしまった。よくない。
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
```cpp:step2.cpp
#include <stack>

class Solution {
    
}
```
