/**

173. Binary Search Tree Iterator [M]

Ref: https://leetcode.com/problems/binary-search-tree-iterator/

 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct TreeNode NODE;

typedef struct 
{
	int curSize;
	int size;
	int *arr;
} BSTIterator;

#define MALLOC_SIZE_UNIT (150)
void inorder(NODE *root, int **ret, int *size)
{
	if (root == NULL)
	{
		return;
	}

	inorder(root->left, ret, size);
	*size += 1;
	if (*size != 0 && *size % MALLOC_SIZE_UNIT == 0)
	{
		*ret = realloc(*ret, sizeof(int)*(*size + MALLOC_SIZE_UNIT));
	}
	(*ret)[(*size)-1] = root->val;
	inorder(root->right, ret, size);
}

BSTIterator* bSTIteratorCreate(struct TreeNode* root) 
{
	BSTIterator *obj = malloc(sizeof(BSTIterator));
	int *arr = malloc(sizeof(int)*MALLOC_SIZE_UNIT);
	int size = 0;
	inorder(root, &arr, &size);

	obj->arr =arr;
	obj->size = size;
	obj->curSize = 0;
	return obj;
}

/** @return the next smallest number */
int bSTIteratorNext(BSTIterator* obj) 
{
	obj->curSize ++;
	return obj->arr[obj->curSize-1];
}

/** @return whether we have a next smallest number */
bool bSTIteratorHasNext(BSTIterator* obj) 
{
	if (obj->curSize == obj->size)
	{
		return false;
	}
	return true;
}

void bSTIteratorFree(BSTIterator* obj) 
{
	free(obj->arr);
	free(obj);
}

/**
 * Your BSTIterator struct will be instantiated and called as such:
 * BSTIterator* obj = bSTIteratorCreate(root);
 * int param_1 = bSTIteratorNext(obj);

 * bool param_2 = bSTIteratorHasNext(obj);

 * bSTIteratorFree(obj);
 */
