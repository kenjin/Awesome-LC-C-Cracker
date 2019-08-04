/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

int addNumHelper(struct ListNode* l1, struct ListNode* l2, int len1, int len2)
{
	if (l1 == NULL)
	{
		return 0;
	}

	int n1 = l1->val, n2 = l2->val;
	int carry = 0;
	if (len1 > len2)
	{
		n2 = 0;
		carry = addNumHelper(l1->next, l2, len1-1, len2);
	} else
	{
		carry = addNumHelper(l1->next, l2->next, len1-1, len2);
	}

	l1->val = n1 + n2 + carry;
	carry = l1->val / 10;
	l1->val %= 10;
	return carry;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{

	int len1 = 0, len2 = 0, carry = 0;
	struct ListNode *tmp = l1;
	while (tmp != NULL)
	{
		len1++;
		tmp = tmp->next;
	}
	tmp = l2;
	while (tmp != NULL)
	{
		len2++;
		tmp = tmp->next;
	}

	// Swap to make sure that l1 is the larger linked list
	if (len1 < len2)
	{
		tmp = l1;
		l1 = l2;
		l2 = tmp;

		int lenTmp = len1;
		len1 = len2;
		len2 = lenTmp;
	}

	carry = addNumHelper(l1, l2, len1, len2);
	if (carry)
	{
		struct ListNode *new = malloc(sizeof(struct ListNode));
		new->val = 1;
		new->next = l1;        
		return new;
	}

	return l1;
}


