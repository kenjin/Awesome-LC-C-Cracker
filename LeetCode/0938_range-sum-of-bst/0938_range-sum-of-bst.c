/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int rangeSumBST(struct TreeNode* root, int L, int R)
{
	if (root == NULL)
	{
		return 0;
	}

	int rRet = 0, lRet = 0;
	if (root->val > L)
	{
		lRet = rangeSumBST(root->left, L, R);
	}
	if (root->val < R)
	{
		rRet = rangeSumBST(root->right, L, R);
	}

	return  (L <= root->val && root->val <= R) ? rRet + lRet + root->val : rRet + lRet;
}

