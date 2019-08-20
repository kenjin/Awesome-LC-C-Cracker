#define ALLOC_UNIT_SIZE 500

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void addRet(int **ret, int *retSize, int val)
{    
	(*ret)[*retSize] = val;
	*retSize += 1;
	if (*retSize % ALLOC_UNIT_SIZE == 0)
	{
		*ret = realloc(*ret, sizeof(int)*(*retSize+ALLOC_UNIT_SIZE));
	}
}

void traverseRightMost(struct TreeNode* root, struct TreeNode* head, int **ret, int *returnSize)
{
	if ((root == NULL) ||
			(root->left == NULL && root->right == NULL))
	{
		return;
	}

	if (root->right)
	{
		traverseRightMost(root->right, head, ret, returnSize);
	} else
	{
		if (root->left && root != head)
		{
			traverseRightMost(root->left, head, ret, returnSize);
		}
	}

	addRet(ret, returnSize, root->val);
}

void traverseLeaf(struct TreeNode* root, int **ret, int *returnSize)
{
	if (root == NULL)
	{
		return;
	}

	if (root->left == NULL && root->right == NULL)
	{
		addRet(ret, returnSize, root->val);
		return;
	}

	if (root->left)
	{
		traverseLeaf(root->left, ret, returnSize);
	}
	if (root->right)
	{
		traverseLeaf(root->right, ret, returnSize);
	}
}

void traverseLeftMost(struct TreeNode* root, struct TreeNode* head, int **ret, int *returnSize)
{
	if ((root == NULL) ||
			(root->left == NULL && root->right == NULL))
	{
		return;
	}

	addRet(ret, returnSize, root->val);

	if (root->left)
	{
		traverseLeftMost(root->left, head, ret, returnSize);
	} else
	{
		if (root->right && root != head)
		{
			traverseLeftMost(root->right, head, ret, returnSize);
		}
	}
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* boundaryOfBinaryTree(struct TreeNode* root, int* returnSize)
{
	int *ret = malloc(sizeof(int)*ALLOC_UNIT_SIZE);
	*returnSize = 0;

	traverseLeftMost(root, root, &ret, returnSize);
	traverseLeaf(root, &ret, returnSize);
	traverseRightMost(root, root, &ret, returnSize);
	// Skip the root node
	if (*returnSize > 1)
	{
		*returnSize -= 1;
	}

	return ret;
}


