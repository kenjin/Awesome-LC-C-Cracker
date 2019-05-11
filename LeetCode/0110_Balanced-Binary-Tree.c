/**

110. Balanced Binary Tree [E]
Ref: https://leetcode.com/problems/balanced-binary-tree/

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:
=> a binary tree in which the depth of the two subtrees of 
   every node never differ by more than 1.

 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int checkBalanced(struct TreeNode* root, bool *ret)
{
	if (root == NULL)
	{
		return 0;
	}
	int hL = checkBalanced(root->left, ret);    
	/* branch pruning */
	if (*ret == false)
	{
		return 0;
	}
	int hR = checkBalanced(root->right, ret);
	if (abs(hL-hR) > 1)
	{
		*ret = false;
	}

	return ((hL > hR ? hL : hR) + 1);        
}

bool isBalanced(struct TreeNode* root)
{
	bool ret = true;
	checkBalanced(root, &ret);
	return ret;
}
