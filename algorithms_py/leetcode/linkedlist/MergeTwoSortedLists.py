# Definition for singly-linked list.
class ListNode(object):
     def __init__(self, x):
         self.val = x
         self.next = None


class Solution(object):
    def mergeTwoLists(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        if l1 is None:
            return l2
        if l2 is None:
            return l1
        dummy = ListNode(0)
        cur = dummy
        nd1, nd2 = l1, l2
        while nd1 is not None or nd2 is not None:
            if nd1 is None:
                cur.next = ListNode(nd2.val)
                nd2 = nd2.next
            elif nd2 is None:
                cur.next = ListNode(nd1.val)
                nd1 = nd1.next
            else:
                if nd1.val < nd2.val:
                    cur.next = ListNode(nd1.val)
                    nd1 = nd1.next
                else:
                    cur.next = ListNode(nd2.val)
                    nd2 = nd2.next
            cur = cur.next
        return dummy.next

