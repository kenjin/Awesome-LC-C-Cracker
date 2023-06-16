/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void traverseHelper(struct TreeNode* root, struct TreeNode **tmp)
{
	if (NULL == root)
	{
		return;
	}

	traverseHelper(root->left, tmp);
	struct TreeNode *cur = *tmp;    
	if (NULL != cur)
	{
		cur->right = root;
		cur->left = NULL;
	}    
	*tmp = root;
	traverseHelper(root->right, tmp);
}

struct TreeNode* increasingBST(struct TreeNode* root)
{
	struct TreeNode *head = NULL;
	struct TreeNode *leftMost = root;
	while (leftMost && leftMost->left)
	{
		leftMost = leftMost->left;
	}
	traverseHelper(root, &head);
	head->left = head->right = NULL;
	return leftMost;
}
