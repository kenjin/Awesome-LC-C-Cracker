
struct TreeNode* LCA(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) 
{
	if (root == NULL)
	{
		return NULL;
	}

	if (root->val < p->val) // Skip left recursion
	{
		return LCA(root->right, p, q);
	} else if (root->val > q->val) // Skip right recursion
	{
		return LCA(root->left, p, q);
	} else
	{
		return root;
	}
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) 
{
	// let p node is smaller than q node
	if (p->val < q->val)
	{
		return LCA(root, p, q);
	} else
	{
		return LCA(root, q, p);
	}
}
