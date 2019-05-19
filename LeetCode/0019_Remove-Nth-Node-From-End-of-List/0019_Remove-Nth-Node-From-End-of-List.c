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
	struct ListNode *curNode = head;
	struct ListNode *preNode = NULL;
	/* 
	 * Create a node is faster n step then original node. 
	 * So when this node enter to the end, we can make 
	 * sure that curNode is the Nth node from the end of 
	 * list.
	 */
	struct ListNode *kFastNode = head;
	for (int i = 0; i < n; i++)
	{
		kFastNode = kFastNode->next;
	}
	while (kFastNode)
	{
		kFastNode = kFastNode->next;
		preNode = curNode;
		curNode = curNode->next;
	}

	/* n is in the head case */
	if (NULL == preNode)
	{
		struct ListNode *delNode = head;
		head = head->next;
	} else
	{
		/* n is in the tail case */
		if (NULL == curNode->next)
		{
			preNode->next = NULL;
		} else
		{
			preNode->next = curNode->next;
		}
	}
	free(curNode);

	return head;
}
