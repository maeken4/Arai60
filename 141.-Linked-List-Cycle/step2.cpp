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
            // cycleが存在する場合、fastとslowは cycleに入りslow-fastは1ずつ減っていきどこかで追いつく。
            ListNode* fast = head;
            ListNode* slow = head;
            while(fast != nullptr){
                if(fast->next != nullptr){
                    fast = fast->next->next;
                }
                else{
                    return false;
                }
                slow = slow->next;
                if(fast == slow){
                    return true;
                }
            }
            return false;
        }
    };