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


bool hasPathSum(struct TreeNode* root, int targetSum)
{
	if (!root)
		return false;
	if (!root->left && !root->right)
		return (targetSum == root->val);

	return (hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val));
}
