/**
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

Note: A leaf is a node with no children.

Example:

Given the below binary tree and sum = 22,

	        5
	       / \
	      4   8
	     /   / \
	    11  13  4
	   /  \    / \
	  7    2  5   1

Return:
[
	[5,4,11,2],
	[5,8,4,5]
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

int maxDepth(struct TreeNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	int maxLeft  = maxDepth(root->left) + 1;
	int maxRight = maxDepth(root->right) + 1;    
	return maxLeft > maxRight ? maxLeft : maxRight;
}

void calSum(int ***ret, int *returnSize, int **columnSizes, int *res, struct TreeNode* node, int sum, int height)
{
	if (node == NULL)
	{        
		return;
	}

	res[height-1] = node->val;
	if (node->left == NULL && node->right == NULL)
	{ 
		int total = 0;
		for (int x = 0; x < height; x++)
		{
			total += res[x];
		}        
		if (total == sum) // Find the correct path
		{
			*returnSize += 1;             
			*ret = realloc(*ret, sizeof(int *)*(*returnSize));
			(*ret)[(*returnSize)-1] = malloc(sizeof(int)*height);            
			*columnSizes = realloc(*columnSizes, sizeof(int)*(*returnSize));
			(*columnSizes)[(*returnSize)-1] = height;
			memcpy((*ret)[(*returnSize)-1], res, sizeof(int)*height);
		}

	} else
	{
		calSum(ret, returnSize, columnSizes, res, node->left,  sum, height+1);
		calSum(ret, returnSize, columnSizes, res, node->right, sum, height+1);
	}
}

int** pathSum(struct TreeNode* root, int sum, int** columnSizes, int* returnSize) {

	int height = maxDepth(root);    
	if (height == 0)
		return NULL;

	int *res = calloc(height, sizeof(int));    
	int **ret = (int **)malloc(sizeof(int *));
	*columnSizes = malloc(sizeof(int));
	*returnSize = 0;

	calSum(&ret, returnSize, columnSizes, res, root, sum, 1/* height-[root] */);

	return ret;
}


