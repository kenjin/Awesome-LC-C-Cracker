/**
236. Lowest Common Ancestor of a Binary Tree [M]

Ref: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool LCA(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q, struct TreeNode** ret)
{
	if (root == NULL)
	{
		return false;
	}

	bool retL = LCA(root->left, p, q, ret);
	/* branch pruning: find the ret */
	if (*ret != NULL)
	{
		return false;
	}
	bool retR = LCA(root->right, p, q, ret);    

	/* My child matched the target, I am the ancestor */
	if (retL && retR)
	{
		*ret = root;
		return false;
	}

	if (root == p || root == q)
	{
		/* One of my child find the target, I am the descendant who match the target of itself */
		if (retL || retR)
		{
			*ret = root;
			return false;
		}
		return true;
	}

	return (retL | retR);    
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode** q) 
{
	struct TreeNode* ret = NULL;
	LCA(root, p, q, &ret);
	return ret;
}
