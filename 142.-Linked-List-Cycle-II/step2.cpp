// Floydの手法

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
   public:
	ListNode *detectCycle(ListNode *head) {
		ListNode *fast = head;
		ListNode *slow = head;

		bool hasCycle = false;
		while (fast != nullptr && fast->next != nullptr) {
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow) {
				hasCycle = true;
				break;
			}
		}
		if (!hasCycle) {
			return nullptr;
		}

		slow = head;
		while (slow != fast) {
			slow = slow->next;
			fast = fast->next;
		}
		return slow;
	}
};
