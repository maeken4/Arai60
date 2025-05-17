


        
#include<set>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr){}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        std::set<ListNode*> s;
        
        ListNode* next = head->next;
        while(next != nullptr){
            if(s.find(next) != s.end()){
                return true;
            }
            s.insert(next);
            next = next->next;
        }
        return false;
    }
};