/**
	Given inorder and postorder traversal of a tree, construct the binary tree.

	Note:
		You may assume that duplicates do not exist in the tree.

	For example, given
		inorder = [9,3,15,20,7]
		postorder = [9,15,7,20,3]

	Return the following binary tree:
		
			    3
			   / \
			  9  20
			    /  \
			   15   7

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* createTree(int* inorder, int in_start, int in_end, int* postorder, int post_start, int post_end)
{
	if (post_start > post_end || in_start > in_end)
	{
		return NULL;
	}

	struct TreeNode* node = malloc(sizeof(struct TreeNode));
	node->val = postorder[post_end];
	int count = 0; // count for postorder
	for (int i = in_start; i <= in_end; i++)
	{            
		if (inorder[i] == postorder[post_end])
		{
			node->left  = createTree(inorder, in_start, i-1, postorder, post_start, post_start+count-1);
			node->right = createTree(inorder, i+1, in_end, postorder, post_start+count, post_end-1);
			break;
		}
		count++;
	}
	return node;
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {

	// Assume two orders are correct for building a BT
	if (inorderSize == 0)
		return NULL;

	return createTree(inorder, 0, inorderSize-1, postorder, 0, postorderSize-1);
}
