/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void traverse(struct TreeNode *root, struct TreeNode **prev, int *min)
{
	if (root == NULL)
	{
		return;
	}

	traverse(root->left, prev, min);    
	if (*prev != NULL)
	{
		int diff = abs((*prev)->val - root->val);
		*min = *min < diff ? *min : diff;
	}
	*prev = root;
	traverse(root->right, prev, min);
}

int minDiffInBST(struct TreeNode* root)
{
	int ret = INT_MAX;
	struct TreeNode *prev = NULL;
	traverse(root, &prev, &ret);

	return ret;
}


