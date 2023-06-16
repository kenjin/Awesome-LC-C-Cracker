/**

84. Largest Rectangle in Histogram [H]
Ref: https://leetcode.com/problems/largest-rectangle-in-histogram/

 */

int largestRectangleArea(int* heights, int heightsSize)
{
	/* Use mark table to skip the index with same height and in current max rectangle */
	char *mark = calloc(heightsSize, sizeof(char));
	int max = 0;
	for (int x = 0; x < heightsSize; x++)
	{
		if (mark[x])
		{
			continue;
		}

		char *tmpMark = calloc(heightsSize, sizeof(char));
		tmpMark[x] = 1;
		int ctr = 1;
		for (int i = x-1; i >= 0; i--)
		{
			if (heights[i] < heights[x])
			{
				break;
			}
			if (heights[i] == heights[x])
			{
				tmpMark[i] = 1;
			}
			ctr++;
		}
		for (int i = x+1; i < heightsSize; i++)
		{
			if (heights[i] < heights[x])
			{
				break;
			}
			if (heights[i] == heights[x])
			{
				tmpMark[i] = 1;
			}
			ctr++;
		}
		if (max < heights[x]*ctr)
		{
			max = heights[x]*ctr;
			memcpy(mark, tmpMark, sizeof(char)*heightsSize);
		}
		free(tmpMark);
	}
	free(mark);
	return max;
}
