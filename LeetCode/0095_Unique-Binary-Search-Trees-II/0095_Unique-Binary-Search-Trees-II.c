/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** createBST(int head, int tail, int *returnSize)
{
	struct TreeNode** ret = malloc(sizeof(struct TreeNode*));
	if (head > tail)
	{
		*returnSize = 1;
		ret[0] = NULL;
		return ret;
	}

	*returnSize = 0;
	for (int i = head; i <= tail; i++)
	{
		int leftSize= 0, rightSize = 0;
		// check sub-tree
		struct TreeNode** l_ret = createBST(head, i-1, &leftSize);
		struct TreeNode** r_ret = createBST(i+1, tail, &rightSize);
		// reallocate return data
		ret = realloc(ret, sizeof(struct TreeNode*)*(leftSize*rightSize+*returnSize));
		for (int x = 0; x < leftSize; x++)
		{
			for (int y = 0; y < rightSize; y++)
			{
				// create root node for current tree
				ret[*returnSize] = malloc(sizeof(struct TreeNode));
				ret[*returnSize]->val = i;
				// update child's node
				ret[*returnSize]->left  = l_ret[x];
				ret[*returnSize]->right = r_ret[y];
				// BST case ++
				*returnSize += 1;
			}
		}
	}
	return ret;
}

struct TreeNode** generateTrees(int n, int* returnSize)
{
	if (n == 0)
	{
		*returnSize = 0;
		return NULL;
	}
	return createBST(1, n, returnSize);
}
