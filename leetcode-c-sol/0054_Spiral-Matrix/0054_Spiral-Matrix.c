/**

54. Spiral Matrix [M]

Ref: https://leetcode.com/problems/spiral-matrix/

 */

#define DIR_SIZE (4)
enum
{
	LEFT = 0,
	TOP,
	RIGHT,
	DOWN,
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
	if (matrixSize == 0)
	{
		*returnSize = 0;
		return NULL;
	}

	char check[matrixSize][matrixColSize[0]];
	memset(check , 0, sizeof(char)*matrixSize*(matrixColSize[0]));

	int direction = RIGHT; 
	int i = 0, j = 0;
	int *ret = malloc(sizeof(int)*matrixSize*(matrixColSize[0]));
	*returnSize = 0;
	while (1)
	{
		if (*returnSize == matrixSize*(matrixColSize[0]))
		{
			break;
		}

		if (i < 0 || i >  (matrixSize-1) || j < 0 || j > (matrixColSize[0]-1) || check[i][j])
		{
			/* Adjust coordinator and change direction */
			if (direction == RIGHT)
			{
				j--;
				i++;
			} else if (direction == LEFT)
			{
				j++;
				i--;
			} else if (direction == TOP)
			{
				i++;
				j++;
			} else
			{
				i--;
				j--;
			}
			direction = (direction + 1) % DIR_SIZE;
		}

		check[i][j] = 1;
		ret[*returnSize] = matrix[i][j];
		*returnSize += 1;
		if (direction == RIGHT)
		{
			j++;
		} else if (direction == LEFT)
		{
			j--;
		} else if (direction == TOP)
		{
			i--;
		} else
		{
			i++;
		}
	}
	return ret;
}
