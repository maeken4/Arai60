#include<set>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr){}
};

// 25m
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        std::set<ListNode*> visited;

        while (head != nullptr) {
            visited.insert(head);
            head = head->next;
            // findにnullptr入れても大丈夫なんだっけ？
            if(visited.find(head) != visited.end()){
                return head;
            }
        }
        return nullptr;
    }
};