/**

270. Closest Binary Search Tree Value [E]

Ref: https://leetcode.com/problems/closest-binary-search-tree-value/

 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int findClosestVal(struct TreeNode* root, double target)
{
	struct TreeNode* nextChild = (root->val > target ? root->left : root->right);
	if (nextChild == NULL)
	{
		return root->val;
	}

	int childRet = findClosestVal(nextChild, target);
	return fabs((double)root->val - target) < fabs((double)childRet - target) ? root->val : childRet;
}

int closestValue(struct TreeNode* root, double target)
{
	return findClosestVal(root, target);
}


