
int minimumTotal(int** triangle, int triangleSize, int* triangleColSize)
{
	int *n1 = calloc(triangleSize, sizeof(int));
	int *n2 = calloc(triangleSize, sizeof(int));
	int ret = INT_MAX;
	n1[0] = triangle[0][0];
	for (int i = 1; i < triangleSize; i++)
	{
		for (int j = 0; j < triangleColSize[i]; j++)
		{            
			if (j > 0 && j < triangleColSize[i]-1)
			{
				int tmp1 = n1[j-1] + triangle[i][j];
				int tmp2 = n1[j] + triangle[i][j];
				n2[j] = tmp1 < tmp2 ? tmp1 : tmp2;
			} else
			{
				n2[j] = (j == 0 ? n1[j] + triangle[i][j] : n1[j-1] + triangle[i][j]);
			}
		}
		memcpy(n1, n2, sizeof(int)*triangleSize);
	}

	for (int i = 0; i < triangleSize; i++)
	{
		ret = ret < n1[i] ? ret : n1[i];
	}
	free(n1);
	free(n2);    
	return ret;
}

