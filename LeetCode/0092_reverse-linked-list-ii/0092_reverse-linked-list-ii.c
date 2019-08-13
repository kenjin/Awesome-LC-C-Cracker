/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* reverseBetween(struct ListNode* head, int m, int n) 
{
	struct ListNode *cur = head;
	struct ListNode *nxt = NULL;
	struct ListNode *pre = NULL;
	struct ListNode *tmp1 = NULL; // node with index m-1
	struct ListNode *tmp2 = NULL; // node with index m
	int ctr = 0;
	for (int i = 1; i <= n; i++) 
	{
		nxt = cur->next;
		if (i == m-1)
		{
			tmp1 = cur;
		}

		if (i >= m)
		{  
			if (i == m)
			{
				tmp2 = cur;
			}
			cur->next = pre;
		}
		pre = cur; 
		cur = nxt;

		if (i == n)
		{
			if (tmp1) // case: m > 0
			{
				tmp1->next = pre;
			} else // case: m = 0
			{
				head = pre;
			}

			tmp2->next = cur;
		}
	}    
	return head;
}

