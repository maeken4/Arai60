struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    // 入力のリストも戻り値のリストもメモリ管理は呼び出し元で行う必要がある。
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* nowNode = head;
        ListNode* resultHead = nowNode ? new ListNode(nowNode->val) : nullptr;
        ListNode* resultTail = resultHead;
        while (nowNode != nullptr) {
            if (nowNode->next == nullptr) {
                break;
                // 次のノードの値が異なる値であれば戻り値のリストに追加する
            } else if (nowNode->val != nowNode->next->val) {
                ListNode* appendNode = new ListNode(nowNode->next->val);
                resultTail->next = appendNode;
                resultTail = resultTail->next;
            }
            // 次のノードも同じ値の場合は何も追加せずに進んでよい
            nowNode = nowNode->next;
        }
        return resultHead;
    }
};
