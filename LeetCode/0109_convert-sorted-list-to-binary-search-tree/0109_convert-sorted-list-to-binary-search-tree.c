/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct TreeNode TREE;
typedef struct ListNode LIST;
LIST* middleNode(LIST* head)
{
	LIST *slow = head;
	LIST *fast = head;

	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}

void updateMid(LIST* head, LIST *ban)
{
	LIST *prev = NULL;
	while (head)
	{
		if (head == ban)
		{
			prev->next = NULL;
			break;
		}
		prev = head;
		head = head->next;        
	}
}

TREE* sortedListToBST(LIST* head)
{
	// Find the middle node
	LIST *mid = middleNode(head);
	if (NULL == mid)
	{
		return NULL;
	}

	TREE *root = malloc(sizeof(TREE));
	root->val = mid->val;

	// Update mid node to NULL
	if (head == mid)
	{
		head = NULL;
	} else
	{
		updateMid(head, mid);
	}

	root->left = sortedListToBST(head);
	root->right = sortedListToBST(mid->next);
	return root;
}

