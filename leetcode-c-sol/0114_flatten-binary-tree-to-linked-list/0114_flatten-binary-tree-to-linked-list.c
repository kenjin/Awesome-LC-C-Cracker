/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct TreeNode NODE;

NODE* flattenHelper(NODE* root)
{
	if (NULL == root)
	{
		return NULL;
	}

	root->left = flattenHelper(root->left);
	root->right = flattenHelper(root->right);

	if (NULL != root->left)
	{
		NODE *tmpRight = root->right;
		NODE *tmpLeftEnd = root->left;

		while (tmpLeftEnd->right != NULL)
		{
			tmpLeftEnd = tmpLeftEnd->right;
		}

		root->right = root->left;
		tmpLeftEnd->right = tmpRight;
		root->left = NULL;
	}
	return root;
}

void flatten(struct TreeNode* root)
{        
	root = flattenHelper(root);
}

