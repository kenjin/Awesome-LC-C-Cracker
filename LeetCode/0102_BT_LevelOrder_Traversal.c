/**
	Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

	For example:
	Given binary tree [3,9,20,null,null,15,7],
		    3	
		   / \
		  9  20
		     /  \
		    15   7
	
	return its level order traversal as:
	[
		[3],
		[9,20],
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
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int maxHeightTree(struct TreeNode* root)
{
	if (root == NULL)
		return 0;
	int maxLeft = maxHeightTree(root->left) + 1;
	int maxRight = maxHeightTree(root->right) + 1;
	return maxLeft > maxRight ? maxLeft : maxRight;
}

int** traverse(struct TreeNode* root, int **ret, int level, int *col)
{
	if (root == NULL)
	{
		return ret;
	}
	ret[level] = (int *)realloc(ret[level], sizeof(int)*(col[level]+1));
	ret[level][(col[level])] = root->val;
	col[level] += 1;    
	ret = traverse(root->left , ret, level+1, col);
	ret = traverse(root->right, ret, level+1, col);

	return ret;
}

int** levelOrder(struct TreeNode* root, int** columnSizes, int* returnSize) {
	if (root == NULL)
		return NULL;    

	*returnSize = maxHeightTree(root);

	int **ret = (int **)malloc(sizeof(int *)*(*returnSize));
	int *colSize = (int *)malloc(sizeof(int)*(*returnSize));
	for (int i = 0; i < (*returnSize); i++)
	{
		ret[i] = (int *)malloc(sizeof(int));
		colSize[i] = 0;
	}

	ret = traverse(root, ret, 0, colSize);
	*columnSizes = colSize;
	return ret;
}


