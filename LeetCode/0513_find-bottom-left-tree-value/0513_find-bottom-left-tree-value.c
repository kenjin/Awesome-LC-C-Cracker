/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void findBottomLeftValueHelper(struct TreeNode* root, int lv, int *max, int *ret)
{
	if (NULL == root)
	{
		return;
	}

	findBottomLeftValueHelper(root->left, lv+1, max, ret);    
	// I am a leftmost node
	if (NULL == root->left)
	{
		if (lv > *max)
		{
			*ret = root->val;
			*max = lv;
		}
	}
	findBottomLeftValueHelper(root->right, lv+1, max, ret);    
}

int findBottomLeftValue(struct TreeNode* root)
{
	int max = 0, ret;
	findBottomLeftValueHelper(root, 1, &max, &ret);        
	return ret;
}


