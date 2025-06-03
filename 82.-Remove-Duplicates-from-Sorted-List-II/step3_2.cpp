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
        ListNode dummy(-1, head);
        ListNode* last_non_duplicate_node = &dummy;
        ListNode* cur_node = last_non_duplicate_node->next;
        while (cur_node && cur_node->next) {
            if (cur_node->val != cur_node->next->val) {
                last_non_duplicate_node = cur_node;
                cur_node = cur_node->next;
                continue;
            }
            int val_to_remove = cur_node->val;
            while (cur_node && cur_node->val == val_to_remove) {
                ListNode* to_delete = cur_node;
                cur_node = cur_node->next;
                delete to_delete;
            }
            last_non_duplicate_node->next = cur_node;
        }
        return dummy.next;
    }
};
