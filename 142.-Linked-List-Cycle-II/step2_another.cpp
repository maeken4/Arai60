// 141での別解のsetを使った解法の流用
#include <set>

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
   public:
	ListNode* detectCycle(ListNode* head) {
		std::set<ListNode*> visited;
		ListNode* now = head;
		while (now != nullptr) {
			if (visited.contains(now)) {
				return now;
			}
			visited.insert(now);
			now = now->next;
		}
		return nullptr;
	}
};
