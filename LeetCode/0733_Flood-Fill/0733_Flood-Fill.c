/**

733. Flood Fill [Easy]

An image is represented by a 2-D array of integers, each integer 
representing the pixel value of the image (from 0 to 65535).

Given a coordinate (sr, sc) representing the starting pixel (row and 
column) of the flood fill, and a pixel value newColor, "flood fill" the
image.

To perform a "flood fill", consider the starting pixel, plus any pixels
connected 4-directionally to the starting pixel of the same color as 
the starting pixel, plus any pixels connected 4-directionally to those 
pixels (also with the same color as the starting pixel), and so on. 
Replace the color of all of the aforementioned pixels with the newColor.

At the end, return the modified image.

Example 1:
Input:
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2

Output: [[2,2,2],[2,2,0],[2,0,1]]

Explanation:
From the center of the image (with position (sr, sc) = (1, 1)), all 
pixels connected by a path of the same color as the starting pixel are 
colored with the new color. Note the bottom corner is not colored 2, 
because it is not 4-directionally connected to the starting pixel.

Note:

The length of image and image[0] will be in the range [1, 50].
The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
The value of each color in image[i][j] and newColor will be an integer in [0, 65535].

 */


void DFS(int **image, int sr, int sc, int maxRow, int maxCol, int **ret, int target, int newColor)
{
	if (sr < 0 || sr >= maxRow || sc < 0 || sc >= maxCol ||
			image[sr][sc] != target || image[sr][sc] == -1)
	{
		return;
	}

	/* Update new color and tag image */
	ret[sr][sc] = newColor;
	int tmp = image[sr][sc];
	image[sr][sc] = -1;

	int dir[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
	for (int i = 0; i < 4; i++)
	{
		DFS(image, sr+dir[i][0], sc+dir[i][1], maxRow, maxCol, ret, target, newColor);
	}

	/* Recover the image */
	image[sr][sc] = tmp;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int newColor, int* returnSize, int** returnColumnSizes)
{
	if (imageSize == 0)
	{
		return image;
	}

	int **ret = malloc(sizeof(int *)*imageSize);
	*returnSize = imageSize;
	*returnColumnSizes = malloc(sizeof(int)*imageSize);
	for (int x = 0; x < imageSize; x++)
	{
		ret[x] = malloc(sizeof(int)*(imageColSize[x]));
		memcpy(ret[x], image[x], sizeof(int)*imageColSize[x]);
		(*returnColumnSizes)[x] = imageColSize[x];
	}

	DFS(image, sr, sc, imageSize, imageColSize[0], ret, image[sr][sc], newColor);

	return ret;
}
