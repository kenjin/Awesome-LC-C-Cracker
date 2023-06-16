/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isUnivalTreeHelper(struct TreeNode *root, int val)
{
	if (!root)
	{
		return true;
	}

	if (root->val != val)
	{
		return false;
	}

	if (!isUnivalTreeHelper(root->left, val))
	{
		return false;
	}

	return isUnivalTreeHelper(root->right, val);
}

bool isUnivalTree(struct TreeNode* root)
{
	if (!root)
	{
		return true;
	}

	return isUnivalTreeHelper(root, root->val);    
}

