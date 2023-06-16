/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int distributeCoinsHelper(struct TreeNode* root, int *ret)
{
	if (root == NULL)
	{
		return 0;
	}

	int tmp = distributeCoinsHelper(root->left, ret) + distributeCoinsHelper(root->right, ret) + root->val;
	*ret += abs(1-tmp);
	root->val = 1;
	return tmp-1;
}


int distributeCoins(struct TreeNode* root)
{
	int ret = 0;
	distributeCoinsHelper(root, &ret);    
	return ret;
}

