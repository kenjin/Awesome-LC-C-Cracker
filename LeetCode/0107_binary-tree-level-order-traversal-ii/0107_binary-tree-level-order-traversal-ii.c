/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void lvOrderTraversalHelper(struct TreeNode* root, int **ret, int* retSize, int** retColSize, int level)
{
	if (root == NULL)
	{
		return;
	}

	lvOrderTraversalHelper(root->left, ret, retSize, retColSize, level-1/* bottom-up */);
	lvOrderTraversalHelper(root->right, ret, retSize, retColSize, level-1/* bottom-up */);

	ret[level] = realloc(ret[level], sizeof(int)*((*retColSize)[level]+1));
	ret[level][(*retColSize)[level]] = root->val;
	(*retColSize)[level] += 1;

}

int getHeight(struct TreeNode *root)
{
	if (root == NULL)
	{
		return 0;
	}

	int l = getHeight(root->left);
	int r = getHeight(root->right);    
	return ( l > r ? l+1 : r+1);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrderBottom(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
	int maxHeight = getHeight(root);
	int **ret = malloc(sizeof(int *)*maxHeight);
	for (int i = 0; i < maxHeight; i++)
	{
		ret[i] = malloc(sizeof(int));
	}

	*returnColumnSizes = calloc(maxHeight, sizeof(int));
	*returnSize = maxHeight;
	lvOrderTraversalHelper(root, ret, returnSize, returnColumnSizes, maxHeight-1 /* bottom-up */);

	return ret;
}


