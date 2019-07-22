/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int leftmost(struct TreeNode* root) 
{
	int count = 0;
	while (root != NULL) 
	{
		count ++;
		root = root->left;
	}
	return count;
}

int countNodesHelper(struct TreeNode* root, int level)
{
	if (root == NULL)
	{
		return 0;
	}

	struct TreeNode *l = root, *r = root;
	// go to left-most child
	int r_leftMost_lv = leftmost(root->right);
	int l_leftMost_lv = level-1;

	int count = 1;    
	if (r_leftMost_lv == l_leftMost_lv) 
	{
		count += (1 << l_leftMost_lv) - 1;
		count += countNodesHelper(root->right, r_leftMost_lv);
	} else
	{
		count += (1 << r_leftMost_lv) - 1;
		count += countNodesHelper(root->left, l_leftMost_lv);
	}

	return count;
}

int countNodes(struct TreeNode* root)
{
	int level = leftmost(root);
	return countNodesHelper(root, level);
}

