/**

142. Linked List Cycle II [Medium]

Given a linked list, return the node where the cycle begins. If there 
is no cycle, return null.

To represent a cycle in the given linked list, we use an integer pos 
which represents the position (0-indexed) in the linked list where tail 
connects to. If pos is -1, then there is no cycle in the linked list.

Note: Do not modify the linked list.

 

Example 1:

Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1

Explanation: There is a cycle in the linked list, where tail connects to the second node.


 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode *chechCycle(struct ListNode *head) 
{
	struct ListNode *fast = head;
	struct ListNode *slow = head;

	while (slow != NULL && fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
		{
			return slow;
		}
	}
	return NULL;
}

struct ListNode *detectCycle(struct ListNode *head) 
{
	struct ListNode *meetPoint = chechCycle(head);

	if (meetPoint == NULL)
	{
		return NULL;
	} else
	{
		/* [R]: root. 
		 * [M]: meet point
		 * [*]: start point in  cycle
		 *
		 *       "X"      "Y"
		 * [R] ------[*]------- [M]---
		 *            |     "Z"      |
		 *		       ---------------
		 *
		 * Distance(Slow) = X + Y          (R->*->M)
		 * Distance(Fast) = X + Y + Y + Z  (R->*->M->*->M)
		 * => Fast travels with double speed and two pointer meet at same time.
		 * => 2*Distance(Slow) = Distance(Fast)
		 * => 2(X+Y) = X+Y+Y+Z
		 * =>      X = Z
		 *
		 * It means that [M] and [R] after a X/Z moves will meet at [*]
		 */

		struct ListNode *root = head;   
		while (meetPoint != NULL && root != NULL && meetPoint != root)
		{
			meetPoint = meetPoint->next;
			root = root->next;
		}
		return root;
	}    
}
