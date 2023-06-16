/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* reverse(struct ListNode* head)
{
	struct ListNode *cur = head;
	struct ListNode *pre = NULL;
	while (cur)
	{
		struct ListNode *tmp = cur->next;
		cur->next = pre;
		pre = cur;
		cur = tmp;
	}

	return pre;
}

struct ListNode* plusOne(struct ListNode* head)
{
	if (head == NULL)
	{
		return NULL;
	}

	struct ListNode *root = reverse(head);
	struct ListNode *tmp = root;

	int carry = 1; // default 1 to plus one
	while (tmp)
	{
		tmp->val += carry;
		carry = (tmp->val == 10 ? 1 : 0);
		tmp->val %= 10;
		tmp = tmp->next;
	}

	root = reverse(root);

	// carry for the most significant digit
	if (carry)
	{
		struct ListNode *newNode = malloc(sizeof(struct ListNode));
		newNode->val = 1;
		newNode->next = root;
		return newNode;
	}

	return root;
}

