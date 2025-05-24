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
        ListNode dummy(0, head);
        ListNode* tail = &dummy;
        while (tail->next && tail->next->next) {
            ListNode* cur_node = tail->next;
            if (cur_node->val != cur_node->next->val) {
                tail = cur_node;
                continue;
            }
            int val_to_remove = cur_node->val;
            while (cur_node && cur_node->val == val_to_remove) {
                ListNode* to_delete = cur_node;
                cur_node = cur_node->next;
                delete to_delete;
            }
            tail->next = cur_node;
        }
        return dummy.next;
    }
};
