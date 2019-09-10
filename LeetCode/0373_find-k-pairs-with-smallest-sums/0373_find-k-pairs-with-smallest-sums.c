typedef struct
{
	int u;
	int v;
	int val;
}NODE;

int compare(const void *a, const void *b)
{
	NODE n1 = *(NODE *)a;
	NODE n2 = *(NODE *)b;

	return n1.val - n2.val;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kSmallestPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize, int** returnColumnSizes)
{
	// Prepare the result to return
	int **ret = malloc(sizeof(int *)*k);
	*returnColumnSizes = malloc(sizeof(int)*k);
	for (int i = 0; i < k; i++)
	{
		ret[i] = calloc(2, sizeof(int));
		(*returnColumnSizes)[i] = 2;
	}    

	NODE *n = malloc(sizeof(NODE)*nums1Size*nums2Size);
	int nCtr = 0;
	for (int i = 0; i < nums1Size; i++)
	{
		for (int j = 0; j < nums2Size; j++)
		{
			n[nCtr].u = nums1[i];
			n[nCtr].v = nums2[j];
			n[nCtr].val = nums1[i] + nums2[j];
			nCtr++;
		}        
	}

	qsort(n, nCtr, sizeof(NODE), compare);
	int x = 0;
	while (x < k && x < nCtr)
	{
		ret[x][0] = n[x].u;
		ret[x][1] = n[x].v;
		x++;
	}
	*returnSize = x;
	free(n);
	return ret;
}
