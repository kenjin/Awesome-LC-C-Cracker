/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
typedef struct TreeNode NODE;

struct TreeNode* insertIntoBST(struct TreeNode* root, int val)
{
	NODE *newNode = malloc(sizeof(NODE));
	newNode->val = val;
	newNode->left = newNode->right = NULL;

	NODE *ret = root;
	while (root != NULL)
	{
		if (root->val < newNode->val)
		{
			if (root->right)
			{
				root = root->right;
			} else
			{
				root->right = newNode;
				break;
			}
		} else if (root->val > newNode->val)
		{
			if (root->left)
			{
				root = root->left;
			} else
			{
				root->left = newNode;
				break;
			}
		}
	}
	return ret;
}


