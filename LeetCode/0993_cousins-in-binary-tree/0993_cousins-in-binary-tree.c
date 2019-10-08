/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* isCousinsHelper(struct TreeNode *root, int *p, int target, int *depth, int pVal, int lv)
{
	if (root == NULL)
	{
		return false;
	}

	if (target == root->val)
	{
		*depth = lv;
		*p = pVal;  
		return true;
	}

	pVal = root->val;    
	if (isCousinsHelper(root->left, p, target, depth, pVal, lv+1))
	{
		return true;
	}
	return isCousinsHelper(root->right, p, target, depth, pVal, lv+1);
}

bool isCousins(struct TreeNode* root, int x, int y)
{
	int xDepth = 0, yDepth = 0;
	int xParent = 0, yParent = 0;
	isCousinsHelper(root, &xParent, x, &xDepth, 0, 0);
	isCousinsHelper(root, &yParent, y, &yDepth, 0, 0);

	return (xDepth == yDepth && xParent != yParent);
}

