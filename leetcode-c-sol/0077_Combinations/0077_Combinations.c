/**

77. Combinations [M]
Ref: https://leetcode.com/problems/combinations/

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

Example:
Input: n = 4, k = 2
Output:
[
[2,4],
[3,4],
[2,3],
[1,2],
[1,3],
[1,4],
]

 */
#define MALLOC_SIZE_UNIT (500)
void combineHelper(int n, int num, int k, int selectCtr, int *tmp, int ***ret, int* returnSize, int** returnColumnSizes)
{
	if (selectCtr+(n-num+1) < k)
	{
		return; 
	}
	if (selectCtr == k)
	{
		*returnSize += 1;
		if (*returnSize != 0 && (*returnSize % MALLOC_SIZE_UNIT) == 0)
		{
			*returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*(*returnSize+MALLOC_SIZE_UNIT));
			*ret = realloc(*ret, sizeof(int *)*(*returnSize+MALLOC_SIZE_UNIT));
		}

		(*ret)[(*returnSize)-1] = calloc(k, sizeof(int));
		memcpy((*ret)[(*returnSize)-1], tmp, sizeof(int)*k);
		(*returnColumnSizes)[(*returnSize)-1] = k;

		return;
	}

	/* select */
	tmp[selectCtr] = num;
	selectCtr++;
	combineHelper(n, num+1, k, selectCtr, tmp, ret, returnSize, returnColumnSizes);
	/* not select*/
	selectCtr--;
	tmp[selectCtr] = 0;
	combineHelper(n, num+1, k, selectCtr, tmp, ret, returnSize, returnColumnSizes);

}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combine(int n, int k, int* returnSize, int** returnColumnSizes)
{
	*returnSize = 0;
	int **ret = malloc(sizeof(int *)*(MALLOC_SIZE_UNIT));
	*returnColumnSizes = malloc(sizeof(int)*(MALLOC_SIZE_UNIT));
	int *tmp = calloc(n, sizeof(int));

	combineHelper(n, 1, k, 0, tmp, &ret, returnSize, returnColumnSizes);

	free(tmp);
	return ret;
}
