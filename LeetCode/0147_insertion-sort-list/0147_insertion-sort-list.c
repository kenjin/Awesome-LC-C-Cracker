/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode NODE;

NODE* insertionSortListHelper(NODE *root, NODE *n)
{
	NODE *tmpRoot = root;
	NODE *prev = NULL;    
	while (root)
	{
		if (root->val >= n->val)
		{
			if (NULL == prev)
			{
				tmpRoot = n;                
			} else
			{
				prev->next = n;
			}
			n->next = root;
			break;
		}
		prev = root;
		root = root->next;
	}

	if (prev)
	{
		prev->next = n;
	} else
	{
		tmpRoot = n;
	}

	return tmpRoot;
}

struct ListNode* insertionSortList(struct ListNode* head)
{
	if (head == NULL)
	{
		return NULL;
	}

	// Add first node, check from the second node
	NODE *root = head;
	NODE *curHead = head->next;
	root->next = NULL;
	while (curHead)
	{
		NODE *tmp = curHead->next;
		curHead->next = NULL;
		root = insertionSortListHelper(root, curHead);         
		curHead = tmp;
	}

	return root;
}

