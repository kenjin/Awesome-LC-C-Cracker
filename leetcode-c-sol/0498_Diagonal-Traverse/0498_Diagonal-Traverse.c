/**
498. Diagonal Traverse [M]

Ref: https://leetcode.com/problems/diagonal-traverse/

 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDiagonalOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
	if (matrixSize == 0)
	{
		*returnSize = 0;
		return NULL;
	}
	/* max diagonal size if sum of row and col at last array*/
	int dSize = (matrixSize-1) + (matrixColSize[0]-1);
	int direction = 1;

	int *ret = malloc(sizeof(int)*matrixSize*matrixColSize[0]);
	*returnSize = 0;

	for (int sum = 0; sum <= dSize; sum++)
	{
		for (int baseRow = 0; baseRow <= sum; baseRow++)
		{
			int row = baseRow;
			int col = sum - row;
			if (direction)
			{
				/* row <-> col */
				int tmp = row;
				row = col;
				col = tmp;
			}
			/* Edge check */
			if (row >= matrixSize || col >= matrixColSize[0] || col < 0 || row < 0)
			{
				continue;
			}
			ret[*returnSize] = matrix[row][col];
			*returnSize += 1;
		}
		direction ^= 1;
	}

	return ret;
}


