// 入力のリストを直接改変する方法

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Soltion {
   public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* currentNode = head;
        while (currentNode != nullptr) {
            // 次のノードの値が条件を満たさない場合、その次のノードにつなげる。
            if (currentNode->next != nullptr && currentNode->val != currentNode->next->val) {
                currentNode->next = currentNode->next->next;
            } else {
                currentNode = currentNode->next;
            }
        }
        return head;
    }
};
