

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target)
{
	if (matrixSize == 0)
	{
		return false;
	}

	int colSize = matrixColSize[0];
	int head = 0;
	int tail = matrixSize*colSize - 1;

	while (head <= tail)
	{        
		int mid = head + (tail-head)/2;
		int r = mid / colSize;
		int c = mid % colSize;
		if (matrix[r][c] < target)
		{
			head = mid+1;
		} else if (matrix[r][c] > target)
		{
			tail = mid-1;
		} else
		{
			return true;
		}
	}

	return false;
}


