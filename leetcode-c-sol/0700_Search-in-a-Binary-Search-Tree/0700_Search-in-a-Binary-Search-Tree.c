/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* searchBST(struct TreeNode* root, int val)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->val == val)
	{
		return root;
	}

	struct TreeNode *retLeft = searchBST(root->left, val);
	if (retLeft != NULL)
	{
		return retLeft;
	}
	struct TreeNode *retRight = searchBST(root->right, val);
	if (retRight != NULL)
	{
		return retRight;
	}

	return NULL;
}


