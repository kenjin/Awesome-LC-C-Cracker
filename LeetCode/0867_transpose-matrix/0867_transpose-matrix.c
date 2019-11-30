
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** transpose(int** A, int ASize, int* AColSize, int* returnSize, int** returnColumnSizes)
{
	int colSize = AColSize[0];

	*returnSize = colSize;
	*returnColumnSizes = malloc(sizeof(int)*colSize);  
	int **ret = malloc(sizeof(int *)*colSize);
	for (int i = 0; i < colSize; i++)
	{
		ret[i] = malloc(sizeof(int)*ASize);
		(*returnColumnSizes)[i] = ASize;
	}

	for (int i = 0; i < colSize; i++)
	{
		for (int j = 0; j < ASize; j++)
		{
			ret[i][j] = A[j][i];
		}       
	}

	return ret;
}

