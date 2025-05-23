struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
	ListNode* RemoveDuplicates(ListNode* head) {
		ListNode* nowNode = head;
		while (nowNode != nullptr) {
			if (nowNode->next == nullptr ||
				nowNode->val != nowNode->next->val) {
				nowNode = nowNode->next;
			} else {
				nowNode->next = nowNode->next->next;
			}
		}
		return head;
	}
};
