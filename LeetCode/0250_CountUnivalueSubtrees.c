/**
  Given a binary tree, count the number of uni-value subtrees.
  A Uni-value subtree means all nodes of the subtree have the same value.

Example :

Input:  root = [5,1,5,5,5,null,5]

	  5
	 / \
	1   5
   / \   \
  5   5   5

Output: 4

*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isUnivalSubtrees(struct TreeNode* root, int *count)
{
	if (root == NULL)
	{
		return true;
	}

	bool ret = true;
	ret &= isUnivalSubtrees(root->left, count);
	ret &= isUnivalSubtrees(root->right, count);
	if (ret == true)
	{
		if ((root->left == NULL || (root->left && root->left->val == root->val))
				&& (root->right == NULL || (root->right && root->right->val == root->val)))
		{
			*count += 1;
			return true;
		}
	}
	return false;
}

int countUnivalSubtrees(struct TreeNode* root) {
	int count = 0;
	isUnivalSubtrees(root, &count);
	return count;
}
