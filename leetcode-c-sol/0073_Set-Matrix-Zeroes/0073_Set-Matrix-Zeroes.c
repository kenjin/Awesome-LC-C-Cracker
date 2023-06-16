/**

73. Set Matrix Zeroes [M]
Ref: https://leetcode.com/problems/set-matrix-zeroes/

Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.

Example 1:
Input: 
[
[1,1,1],
[1,0,1],
[1,1,1]
]
Output: 
[
[1,0,1],
[0,0,0],
[1,0,1]
]

Example 2:
Input: 
[
[0,1,2,0],
[3,4,5,2],
[1,3,1,5]
]
Output: 
[
[0,0,0,0],
[0,4,5,0],
[0,3,1,0]
]

Follow up:
- A straight forward solution using O(mn) space is probably a bad idea.
- A simple improvement uses O(m + n) space, but still not the best solution.
- Could you devise a constant space solution?

 */
void setZeroes(int** matrix, int matrixSize, int* matrixColSize)
{
	if (matrixSize == 0)
	{
		return;
	}

	char row[matrixSize];
	char col[matrixColSize[0]];

	memset(row, 0, sizeof(char)*matrixSize);
	memset(col, 0, sizeof(char)*matrixColSize[0]);

	/* Use two flags(col0, row0) to indicate that first row and col zero case */
	int col0 = 0, row0 = 0;
	for (int i = 0; i < matrixSize; i++)    
	{
		if (matrix[i][0] == 0)
		{
			col0 = 1;
			break;
		}
	}

	for (int i = 0; i < matrixColSize[0]; i++)    
	{
		if (matrix[0][i] == 0)
		{
			row0 = 1;
			break;
		}
	}

	/* 
	 * Use first row and col as a flag to record the whole row[1..m] and col[1..n] zero case 
	 * set flag to zero to indicate each row/col need to set to zero or not
	 */
	for (int i = 1; i < matrixSize; i++)
	{
		for (int j = 1; j < matrixColSize[0]; j++)
		{
			if (matrix[i][j] == 0)
			{
				matrix[i][0] = 0;
				break;
			}
		}
	}
	for (int j = 1; j < matrixColSize[0]; j++)
	{
		for (int i = 1; i < matrixSize; i++)
		{
			if (matrix[i][j] == 0)
			{
				matrix[0][j] = 0;
				break;
			}
		}
	}
	/* Update zero via checking first row/col */
	for (int i = 1; i < matrixSize; i++)
	{
		if (matrix[i][0] == 0)
		{
			for (int j = 1; j < matrixColSize[0]; j++)
			{
				matrix[i][j] = 0;
			}           
		}
	}
	for (int j = 1; j < matrixColSize[0]; j++)
	{
		if (matrix[0][j] == 0)
		{
			for (int i = 1; i < matrixSize; i++)
			{
				matrix[i][j] = 0;
			}           
		}
	}
	/* Update first row and col */
	if (col0)
	{
		for (int i = 0; i < matrixSize; i++)    
		{
			matrix[i][0] = 0;
		}
	}
	if (row0)
	{
		for (int j = 0; j < matrixColSize[0]; j++)    
		{
			matrix[0][j] = 0;
		}
	}
}
