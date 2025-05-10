// PRを受け修正

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
    public:
    bool hasCycle(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;

        while(fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow) {
                return true;
            }
        }
        return false;
    }
};