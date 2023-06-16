
void addOneRowHelper(struct TreeNode* root, int v, int d, int curD)
{
	if (root == NULL)
	{
		return;
	}

	if (d == curD+1)
	{
		struct TreeNode *nL = calloc(1, sizeof(struct TreeNode));
		struct TreeNode *nR = calloc(1, sizeof(struct TreeNode));
		nL->val = v;
		nR->val = v;
		nL->left = root->left;
		nR->right = root->right;
		root->left = nL;
		root->right = nR;
	} else
	{
		addOneRowHelper(root->left, v, d, curD+1);
		addOneRowHelper(root->right, v, d, curD+1);
	}    
}

struct TreeNode* addOneRow(struct TreeNode* root, int v, int d)
{
	if (d == 1)
	{
		struct TreeNode *n = calloc(1, sizeof(struct TreeNode));
		n->val = v;
		n->left = root;
		return n;
	}
	addOneRowHelper(root, v, d, 1);
	return root;
}


