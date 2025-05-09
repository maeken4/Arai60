# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None
# 6m
class Solution:
    def hasCycle(self, head: ListNode | None) -> bool:
        fast: ListNode = head;
        slow: ListNode = head;
        while fast is not None:
            if fast.next is not None:
                fast = fast.next.next
                slow = slow.next
                if fast is slow:
                    return True
            else:
                return False
        return False