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
		ListNode* nowNode = head;
		ListNode* resultHead = nowNode ? new ListNode(nowNode->val) : nullptr;
		ListNode* resultTail = resultHead;
		while (nowNode) {
			if (nowNode->next == nullptr) {
				break;
			} else if (nowNode->val != nowNode->next->val) {
				ListNode* append = new ListNode(nowNode->next->val);
			}
			// 次のノードも同じ値の場合は何も追加せずに進む
			nowNode = nowNode->next;
		}
		return resultHead;
	}
};
