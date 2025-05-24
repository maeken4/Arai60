// 入力のリストを改変する解法

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* tail = head;
        while (tail != nullptr) {
            if (tail->next == nullptr || tail->val != tail->next->val) {
                tail = tail->next;
            } else {
                ListNode* toDelete = tail->next;
                tail->next = tail->next->next;
                delete toDelete;
            }
        }
        return head;
    }
};
