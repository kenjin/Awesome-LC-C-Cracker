#define MAX_PATH_STR_SIZE   5000

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool binaryTreePathsHelper(struct TreeNode* root, char *str, int strIdx, char ***ret, int* returnSize)
{
	if (NULL == root)
	{
		return true;
	}

	char buf[12] = {0};
	sprintf(buf, "->%d", root->val);
	int len = strlen(buf);       
	memcpy(&(str[strIdx]), buf, sizeof(char)*len);
	strIdx += len;

	bool retLeft = binaryTreePathsHelper(root->left, str, strIdx, ret, returnSize);
	bool retRight = binaryTreePathsHelper(root->right, str, strIdx, ret, returnSize);        
	// Lead Node
	if (retLeft && retRight)
	{
		str[strIdx] = 0;
		*ret = realloc(*ret, sizeof(char *)*(*returnSize+1));
		(*ret)[*returnSize] = calloc(MAX_PATH_STR_SIZE, sizeof(char));
		strcpy((*ret)[*returnSize], &(str[2]));
		*returnSize += 1;        
	}

	return false;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** binaryTreePaths(struct TreeNode* root, int* returnSize)
{
	char **ret = malloc(sizeof(char*));
	char *str = calloc(MAX_PATH_STR_SIZE, sizeof(char));
	*returnSize = 0;
	binaryTreePathsHelper(root, str, 0, &ret, returnSize);

	free(str);
	return ret;
}

