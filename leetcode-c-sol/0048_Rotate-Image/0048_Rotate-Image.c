/**

48. Rotate Image
Ref: https://leetcode.com/problems/rotate-image/


Rotate the image by 90 degrees (clockwise).

Note:
You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:
Given input matrix = 
[
	[1,2,3],
	[4,5,6],
	[7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
	[7,4,1],
	[8,5,2],
	[9,6,3]
]

Example 2:
Given input matrix =
[
	[ 5, 1, 9,11],
	[ 2, 4, 8,10],
	[13, 3, 6, 7],
	[15,14,12,16]
], 

rotate the input matrix in-place such that it becomes:
[
	[15,13, 2, 5],
	[14, 3, 4, 1],
	[12, 6, 8, 9],
	[16, 7,10,11]
]

 */

void rotate(int** matrix, int matrixSize, int* matrixColSize)
{
	int halfSize = matrixSize/2;
	for (int i = 0; i < halfSize; i++) 
	{
		for (int j = i; j < matrixSize-i-1; j++) 
		{            
			int tmp = matrix[i][j];
			int rotateI = matrixSize-i-1;
			int rotateJ = matrixSize-j-1;
			matrix[i][j] = matrix[rotateJ][i];
			matrix[rotateJ][i] = matrix[rotateI][rotateJ];
			matrix[rotateI][rotateJ] = matrix[j][rotateI];
			matrix[j][rotateI] = tmp;
		}
	}
}
