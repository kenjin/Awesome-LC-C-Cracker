/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void minDepthHelper(struct TreeNode* root, int ctr, int *ret)
{
	if (root && NULL == root->left && NULL == root->right)
	{
		*ret = *ret < ctr ? *ret : ctr; 
		return;
	}

	if (root->left)
	{
		minDepthHelper(root->left, ctr+1, ret);
	}
	if (root->right)
	{
		minDepthHelper(root->right, ctr+1, ret);
	}
}

int minDepth(struct TreeNode* root)
{
	if (NULL == root)
	{
		return 0;
	}

	int ret = INT_MAX;
	minDepthHelper(root, 1, &ret);
	return ret;
}


