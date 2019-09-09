
int kthSmallest(int** matrix, int matrixSize, int* matrixColSize, int k)
{
	int head = matrix[0][0];
	int tail = matrix[matrixSize-1][matrixSize-1]; // because of n x "n" matrix (dont care matrixColSize)    
	int j; // use this index to get column index for the upper bound of ascending matrix[]
	while (head < tail)
	{
		int mid = head + (tail - head)/2;
		int ctr = 0;
		for (int i = 0; i < matrixSize; i++)
		{
			// Find the column upper bound
			for (j = 0; j < matrixSize; j++)
			{
				if (matrix[i][j] > mid)
				{
					break;
				}
			}

			ctr += j;
			if (j == 0 || ctr >= k)
			{
				break;
			}
		}

		if (ctr < k)
		{
			head = mid + 1;
		} else
		{
			tail = mid;
		}
	}

	return tail;
}

