/**
  240. Search a 2D Matrix II  [Medium]
  Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

  Integers in each row are sorted in ascending from left to right.
  Integers in each column are sorted in ascending from top to bottom.

Example:

Consider the following matrix:

[
	[1,   4,  7, 11, 15],
	[2,   5,  8, 12, 19],
	[3,   6,  9, 16, 22],
	[10, 13, 14, 17, 24],
	[18, 21, 23, 26, 30]
]

Given target = 5, return true.

Given target = 20, return false.

 */

bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) 
{
	if (matrixRowSize == 0 || matrixColSize == 0)
	{
		return false;
	}    
	if (target < matrix[0][0] || target > matrix[matrixRowSize-1][matrixColSize-1])
	{
		return false;
	}

	/* Start from the lower left corner
	 * 1) < target => x--
	 * 2) > target => y++
	 *
	 * Worst case: O(rowSize+colSize)
	 */
	int start_x = matrixRowSize-1;
	int start_y = 0;
	while (start_x >= 0 && start_y < matrixColSize)
	{
		if (target < matrix[start_x][start_y])
		{
			start_x--;
		} else if (target > matrix[start_x][start_y])
		{
			start_y++;
		} else
		{
			return true;
		}        
	}

	return false;
}
