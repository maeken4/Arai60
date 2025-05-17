#include<set>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
    public:
    bool hasCycle(ListNode* head) {
        std::set<ListNode*> visited;
        ListNode* now = head;
        while(now != nullptr) {
            if (visited.contains(now)) {
                return true;
            }
            visited.insert(now);
            now = now->next;
        }
        return false;
    }
};