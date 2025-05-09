#include<map>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// いろいろおかしいのでstep2_another.cppで修正して動かす
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr){}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        std::set<ListNode> s;
        
        ListNode* next = head->next;
        while(next != NULL){
            if(s.find(next)){
                return true;
            }

            s.insert(next);

        }
        return false;
    }
};