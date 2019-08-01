/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* deleteDuplicates(struct ListNode* head)
{
	if (head == NULL)
	{
		return head;
	}

	struct ListNode *pre = head;
	struct ListNode *cur = head->next;    
	while (cur)
	{
		if (cur->val == pre->val)
		{
			pre->next = cur->next;
			cur = cur->next;
		} else
		{
			pre = cur;
			cur = cur->next;
		}
	}

	return head;
}

