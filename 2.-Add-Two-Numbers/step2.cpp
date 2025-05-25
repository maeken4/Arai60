struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(-1, nullptr);
        ListNode* tail = &dummy;
        int carry = 0;
        while (l1 || l2 || carry) {
            // l1, l2がnullptrだった場合0ノードを一時的に設定する。このブロックを抜けると解放される。
            ListNode fake(0);
            l1 = l1 ? l1 : &fake;
            l2 = l2 ? l2 : &fake;

            int total = l1->val + l2->val + carry;
            carry = total / 10;
            tail->next = new ListNode(total % 10, nullptr);
            tail = tail->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        return dummy.next;
    }
};
