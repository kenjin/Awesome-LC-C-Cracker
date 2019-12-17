/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int sumNumbersHelper(struct TreeNode* root, int cur)
{
	if (NULL == root)
	{
		return 0;
	}

	cur = cur*10 + root->val;
	if (NULL == root->left && NULL == root->right)
	{
		return cur;
	}

	return sumNumbersHelper(root->left, cur) + sumNumbersHelper(root->right, cur);
}

int sumNumbers(struct TreeNode* root)
{
	return sumNumbersHelper(root, 0);
}


