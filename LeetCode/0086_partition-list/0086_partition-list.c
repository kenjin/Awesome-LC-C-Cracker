typedef struct ListNode NODE;

struct ListNode* partition(struct ListNode* head, int x)
{
	NODE *h1 = calloc(1, sizeof(NODE));
	NODE *h2 = calloc(1, sizeof(NODE));

	NODE *tmp = head, *p1 = h1, *p2 = h2;
	while (tmp)
	{
		if (tmp->val < x)
		{
			p1->next = tmp;
			p1 = p1->next;
		} else
		{
			p2->next = tmp;
			p2 = p2->next;
		}
		tmp = tmp->next;
	}

	p1->next = h2->next;
	p2->next = NULL;    
	head = h1->next;
	free(h1);
	free(h2);    
	return head;
}


