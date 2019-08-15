/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) 
{
	if (root == NULL)
	{
		return NULL;
	}

	if (root == p || root == q)
	{
		return root;
	}

	struct TreeNode *l = lowestCommonAncestor(root->left, p, q);
	struct TreeNode *r = lowestCommonAncestor(root->right, p, q);

	if (l != NULL && r != NULL)
	{
		return root;
	} else if (l == NULL && r == NULL)
	{
		return NULL;
	} else
	{
		return (l != NULL ? l : r);
	}
}
