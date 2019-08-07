void reorderList(struct ListNode* head)
{
	if (head == NULL)
	{
		return;
	}

	struct ListNode *fast = head;
	struct ListNode *slow = head;    
	int slowLen = 0;
	while (fast && fast->next)
	{
		slowLen++;
		fast = fast->next->next;
		slow = (fast == NULL ? slow : slow->next);
	}

	// simple stack
	struct ListNode **s = malloc(sizeof(struct ListNode *)*(slowLen+1));
	int ctr = 0;
	struct ListNode *tmp = slow->next;
	while (tmp)
	{
		s[ctr] = tmp;
		ctr++;
		tmp = tmp->next;
	}

	for (int i = ctr-1; i >=0 ;i--)
	{        
		tmp = head->next;
		head->next = s[i];
		s[i]->next = tmp;
		head = tmp;
	}

	if (tmp)
	{
		tmp->next = NULL;
	}

	free(s);
}
