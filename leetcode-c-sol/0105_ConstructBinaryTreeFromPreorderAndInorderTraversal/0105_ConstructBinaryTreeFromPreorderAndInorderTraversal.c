/**
105. Construct Binary Tree from Preorder and Inorder Traversal [Medium]

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
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


struct TreeNode* createTree(int* inorder, int in_start, int in_end, int* preorder, int pre_start, int pre_end)
{
	if (pre_start > pre_end || in_start > in_end)
	{
		return NULL;
	}

	struct TreeNode* node = malloc(sizeof(struct TreeNode));
	node->val = preorder[pre_start];
	int count = 0; // count for preorder
	for (int i = in_start; i <= in_end; i++)
	{            
		if (inorder[i] == preorder[pre_start])
		{
			node->left  = createTree(inorder, in_start, i-1, preorder, pre_start+1, pre_start+count);
			node->right = createTree(inorder, i+1, in_end, preorder, pre_start+1+count, pre_end);
			break;
		}
		count++;
	}
	return node;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    return createTree(inorder, 0, inorderSize-1, preorder, 0, preorderSize-1);
}


