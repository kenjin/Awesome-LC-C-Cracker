/**

112. Path Sum [Easy]

Ref: https://leetcode.com/problems/path-sum/

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool calSum(struct TreeNode* root, int sum, int target)
{    
	if (root == NULL)
	{
		return (sum == target ? true : false);
	}

	target += root->val;
	bool bL = false;
	bool bR = false;

	if (root->right == NULL || root->left != NULL)
	{
		bL = calSum(root->left, sum, target);
	}

	if ((bL == false) && /* Branch pruning */
			(root->left == NULL || root->right != NULL))
	{
		bR = calSum(root->right, sum, target);
	}

	return (bL | bR);
}

bool hasPathSum(struct TreeNode* root, int sum)
{
	if (root == NULL)
	{
		return false;
	}
	return calSum(root, sum, 0);
}
