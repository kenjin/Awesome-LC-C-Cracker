/**

19. Remove Nth Node From End of List [M]
Ref: https://leetcode.com/problems/remove-nth-node-from-end-of-list/

Given a linked list, remove the n-th node from the end of list and return its head.

Example:
Given linked list: 1->2->3->4->5, and n = 2.
After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:
Given n will always be valid.

Follow up:
Could you do this in one pass?

 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* removeNthFromEnd(struct ListNode* head, int n)
{
	struct ListNode *p1 = head, *p2 = head, *prev = NULL;
	for (int i = 0; i < n; i++)
		p1 = p1->next;

	while (p1) {
		p1 = p1->next;
		prev = p2;
		p2 = p2->next;
	}
	if (!prev)
		head = head->next;
	else
		prev->next = p2->next;

	free(p2);
	return head;
}
