/**

61. Rotate List [M]

Given a linked list, rotate the list to the right by k places, where k is non-negative.

Example 1:

Input: 1->2->3->4->5->NULL, k = 2
Output: 4->5->1->2->3->NULL

Explanation:
rotate 1 steps to the right: 5->1->2->3->4->NULL
rotate 2 steps to the right: 4->5->1->2->3->NULL
Example 2:


Input: 0->1->2->NULL, k = 4
Output: 2->0->1->NULL

Explanation:
rotate 1 steps to the right: 2->0->1->NULL
rotate 2 steps to the right: 1->2->0->NULL
rotate 3 steps to the right: 0->1->2->NULL
rotate 4 steps to the right: 2->0->1->NULL

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode NODE;
struct ListNode* rotateRight(struct ListNode* head, int k)
{        
	NODE *tmp = head;
	if (tmp == NULL)
	{
		return NULL;
	} else /* Non-empty Case (It means pre node must exist) */
	{
		NODE *pre = NULL;
		int count = 0;
		/* Count the len of the list, and update TAIL->next to HEAD to create a cycle */
		while (tmp != NULL)
		{
			count++;
			pre = tmp;
			tmp = tmp->next;
		}
		pre->next = head;

		k = count - (k % count);
		count = 0;
		while (head != NULL)
		{
			/* Find new head */
			if (count == k)
			{
				pre->next = NULL;
				break;
			}        
			count++;
			pre = head;
			head = head->next;
		}    
		return head;
	}
}
