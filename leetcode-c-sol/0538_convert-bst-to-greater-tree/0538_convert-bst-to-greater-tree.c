/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


void convertBSTHelper(struct TreeNode *root, int *sum)
{
	if (root == NULL)
	{
		return;
	}

	convertBSTHelper(root->right, sum);
	*sum += root->val;
	root->val = *sum; 
	convertBSTHelper(root->left, sum);   
}

struct TreeNode* convertBST(struct TreeNode* root)
{
	int sum = 0;
	convertBSTHelper(root, &sum);    
	return root;
}

