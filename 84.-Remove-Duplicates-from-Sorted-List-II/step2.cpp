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
        // スタック上に動的確保することで開放しなくてよくなる
        ListNode dummy(0, head);
        ListNode* tail = &dummy;
        // tailまでは重複がないとして次のノードから確認する
        while (tail->next && tail->next->next) {
            if (tail->next->val != tail->next->next->val) {
                tail = tail->next;
            } else {
                // 重複を検知した場合、値が被っている間ノードを消していく
                int val_to_remove = tail->next->val;
                while (tail->next && tail->next->val == val_to_remove) {
                    ListNode* toDelete = tail->next;
                    tail->next = tail->next->next;
                    delete toDelete;
                }
            }
        }
        return dummy.next;
    }
};
