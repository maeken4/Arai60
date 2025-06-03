#include <map>
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
        // 値の登場回数を管理する
        std::map<int, int> count;
        for (ListNode* p = head; p != nullptr; p = p->next) {
            count[p->val]++;
        }
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* tail = dummy;
        while (tail != nullptr && tail->next != nullptr) {
            if (count[tail->next->val] > 1) {
                tail->next = tail->next->next;
            } else {
                tail = tail->next;
            }
        }
        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
    }
};
