/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int get_bst_node(struct TreeNode* root)
{
	if (!root)
		return 0;

	return get_bst_node(root->left) + get_bst_node(root->right) + 1;
}

void inorder_traverse(struct TreeNode* root, int *list, int *ctr)
{
	if (!root)
		return;

	inorder_traverse(root->left, list, ctr);
	list[*ctr] = root->val;
	*ctr += 1;
	inorder_traverse(root->right, list, ctr);
}

bool isValidBST(struct TreeNode* root)
{
	int tree_nodes = get_bst_node(root);
	if (tree_nodes < 2)
		return true;

	int list[tree_nodes], ctr = 0;
	inorder_traverse(root, list, &ctr);
	for (int x = 1; x < tree_nodes; x++) {
		if (list[x-1] >= list[x])
			return false;
	}
	return true;
}
