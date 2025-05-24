// 戻り値用に新しくリストを作る方針

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
        if (head == nullptr) {
            return nullptr;
        }
        ListNode* now = head;
        ListNode* ans = new ListNode(head->val);
        ListNode* ansNow = ans;
        while (now != nullptr && now->next != nullptr) {
            if (now->val != now->next->val) {
                ListNode* append = new ListNode(now->next->val);
                ansNow->next = append;
                ansNow = ansNow->next;
            }
            now = now->next;
        }
        return ans;
    }
};
