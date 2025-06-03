#include <memory>

struct ListNode {
    int val;
    std::unique_ptr<ListNode> next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, std::unique_ptr<ListNode> next) : val(x), next(std::move(next)) {}
};

class Solution {
   public:
    std::unique_ptr<ListNode> removeDuplicate(std::unique_ptr<ListNode> head) {
        std::unique_ptr<ListNode> dummy = std::make_unique<ListNode>(0);
        dummy->next = std::move(head);
        std::unique_ptr<ListNode>* tail = &dummy->next;

        while (*tail && (*tail)->next) {
            if ((*tail)->val != (*tail)->next->val) {
                tail = &(*tail)->next;
            } else {
                int val_to_remove = (*tail)->val;
                while (*tail && (*tail)->val == val_to_remove) {
                    *tail = std::move((*tail)->next);  // 外れたノードは自動で delete
                }
            }
        }
        return std::move(dummy->next);
    }
};
