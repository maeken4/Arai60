// 戻り値用に新しくリストを作る解答

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == nullptr) {
			return nullptr;
		}
		ListNode* currentNode = head;
		ListNode* resultHead = new ListNode(head->val);
		ListNode* resultTail = resultHead;
		while (currentNode != nullptr && currentNode->next != nullptr) {
			if (currentNode->next != nullptr &&
				currentNode->val == currentNode->next->val) {
				currentNode->next = currentNode->next->next;
			} else {
				ListNode* append = new ListNode(currentNode->next->val);
				currentNode = currentNode->next;
				resultTail->next = append;
				resultTail = resultTail->next;
			}
		}
		return resultHead;
	}
};
