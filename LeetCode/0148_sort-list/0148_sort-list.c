typedef struct ListNode NODE;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
NODE* middleNode(NODE* head)
{
	NODE *slow = head;
	NODE *fast = head;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

struct ListNode* mergeList(struct ListNode* l_head, struct ListNode* r_head)
{
	// Consider the empty linked list case
	if (l_head == NULL || r_head == NULL)
	{
		if (l_head == NULL && r_head == NULL)
		{
			return NULL;
		}
		return (r_head != NULL ? r_head : l_head);
	} 

	NODE *retNode = NULL;
	// Choose the new head pointer
	if (l_head->val < r_head->val)
	{
		retNode = l_head;
		l_head = l_head->next;
	} else
	{
		retNode = r_head;
		r_head = r_head->next;
	}

	// Merge List => O(n)
	NODE *tmp = retNode;
	while (l_head && r_head)
	{
		if (l_head->val < r_head->val)
		{
			tmp->next = l_head;
			l_head = l_head->next;
		} else
		{
			tmp->next = r_head;
			r_head = r_head->next;
		}
		tmp = tmp->next;
	}

	while (l_head)
	{
		tmp->next = l_head;
		l_head = l_head->next;
		tmp = tmp->next;
	}
	while (r_head)
	{
		tmp->next = r_head;
		r_head = r_head->next;
		tmp = tmp->next;
	}

	tmp = NULL;
	return retNode;
}

struct ListNode* sortList(struct ListNode* head)
{
	// Case: length of linked list <= 1
	if (NULL == head || NULL == head->next)
	{
		return head;
	}
	// Case: length of linked list > 1
	// Get middle of the Linked List => O(n)
	NODE *midNode = middleNode(head);

	// Split to two half linked list
	NODE *tmp = head;
	NODE *pre = NULL;
	while (tmp != midNode)
	{
		pre = tmp;
		tmp = tmp->next;
	}
	pre->next = NULL;

	// Recursive Merge Sort
	NODE *l_head = sortList(head);
	NODE *r_head = sortList(midNode);

	return mergeList(l_head, r_head);
}

