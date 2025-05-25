レビューの利便性のため、各ステップで書いたコードはこちらにも転記してみます。

# step1
素直に繰り上がりを記録しながら足していく方針で解いた。
```cpp
class Solution {
   public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0, nullptr);
        ListNode* tail = &dummy;
        int carry = 0;
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int val = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
            carry = val / 10;
            ListNode* append = new ListNode(val % 10, nullptr);
            tail->next = append;
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
            tail = tail->next;
        }
        return dummy.next;
    }
};
```
