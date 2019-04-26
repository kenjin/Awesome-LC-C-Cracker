/**

103. Binary Tree Zigzag Level Order Traversal [Medium]
  
Given a binary tree, return the zigzag level order traversal of its 
nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7

return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]

 */


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int maxHeightTree(struct TreeNode* root)
{
	if (root == NULL)
		return 0;
	int maxLeft = maxHeightTree(root->left) + 1;
	int maxRight = maxHeightTree(root->right) + 1;
	return maxLeft > maxRight ? maxLeft : maxRight;
}

int** levelOrderTraverse(struct TreeNode* root, int **ret, int level, int *col)
{
	if (root == NULL)
	{
		return ret;
	}
	ret[level] = (int *)realloc(ret[level], sizeof(int)*(col[level]+1));
	ret[level][(col[level])] = root->val;
	col[level] += 1;
	ret = levelOrderTraverse(root->left , ret, level+1, col);
	ret = levelOrderTraverse(root->right, ret, level+1, col);

	return ret;
}

void reverse(int *ret, int start, int end)
{
    if (start > end)
    {
        return;
    }

    int tmp = ret[start];
    ret[start] = ret[end];
    ret[end] = tmp;
    reverse(ret, start+1, end-1);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
	*returnSize = maxHeightTree(root);

    if (!(*returnSize))
    {
        return NULL;
    }
	int **ret = (int **)malloc(sizeof(int *)*(*returnSize));
	*returnColumnSizes = (int *)calloc((*returnSize), sizeof(int));
	for (int i = 0; i < (*returnSize); i++)
	{
		ret[i] = (int *)malloc(sizeof(int));
	}

    ret = levelOrderTraverse(root, ret, 0, *returnColumnSizes);

    /* zigzag level process */
    for (int x = 1; x < *returnSize; x+=2)
    {
        reverse(ret[x], 0, (*returnColumnSizes)[x]-1);
    }

    return ret;

}
