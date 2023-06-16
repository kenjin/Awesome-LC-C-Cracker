/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int diameterOfBinaryTreeHelper(struct TreeNode* root, int *maxAns)
{
	if (root == NULL)
	{
		return 0;
	}

	int hL = diameterOfBinaryTreeHelper(root->left, maxAns);
	int hR = diameterOfBinaryTreeHelper(root->right, maxAns);

	if (*maxAns < hL+hR)
	{
		*maxAns = hL + hR;
	}

	return (hL > hR ? hL : hR) + 1;
}

int diameterOfBinaryTree(struct TreeNode* root)
{
	int max = 0;
	diameterOfBinaryTreeHelper(root, &max);

	return max;
}

