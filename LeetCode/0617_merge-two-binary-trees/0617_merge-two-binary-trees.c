/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct TreeNode NODE;

struct TreeNode* mergeTrees(struct TreeNode* t1, struct TreeNode* t2)
{
	if (t1 == NULL && t2 == NULL)
	{
		return NULL;
	}

	NODE *n = calloc(1, sizeof(NODE));
	if (t1 != NULL)
	{
		n->val += t1->val;
	}
	if (t2 != NULL)
	{
		n->val += t2->val;
	}

	NODE *leftChild1 = (t1 == NULL ? NULL : t1->left);
	NODE *leftChild2 = (t2 == NULL ? NULL : t2->left);    
	n->left = mergeTrees(leftChild1, leftChild2);

	NODE *rightChild1 = (t1 == NULL ? NULL : t1->right);
	NODE *rightChild2 = (t2 == NULL ? NULL : t2->right);    
	n->right = mergeTrees(rightChild1, rightChild2);

	return n;
}

