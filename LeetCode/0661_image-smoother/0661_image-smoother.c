
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** imageSmoother(int** M, int MSize, int* MColSize, int* returnSize, int** returnColumnSizes)
{
	char dir[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
	int mColSize = MColSize[0];
	int **ret = malloc(sizeof(int*)*MSize);
	*returnColumnSizes = malloc(sizeof(int)*MSize);
	*returnSize = MSize;
	for (int i = 0; i < MSize; i++)
	{
		ret[i] = malloc(sizeof(int)*mColSize);
		(*returnColumnSizes)[i] = mColSize;
	}

	for (int i = 0; i < MSize; i++)
	{
		for (int j = 0; j < mColSize; j++)
		{
			int ctr = 1;
			int sum = M[i][j];
			int row, col;
			for (int x = 0; x < 8; x++)
			{
				row = i + dir[x][0];
				col = j + dir[x][1];
				if (row < 0 || row >= MSize ||
						col < 0 || col >= mColSize)
				{
					continue;
				}
				ctr++;
				sum += M[row][col];
			}
			ret[i][j] = sum / ctr;
		}
	}

	return ret;
}


