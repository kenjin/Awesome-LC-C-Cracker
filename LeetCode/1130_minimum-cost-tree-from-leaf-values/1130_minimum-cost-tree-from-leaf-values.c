
int mctFromLeafValues(int* arr, int arrSize)
{
	int **dp = malloc(sizeof(int *)*arrSize);
	int **max = malloc(sizeof(int *)*arrSize);
	for (int i = 0; i < arrSize; i++)
	{
		dp[i] = calloc(arrSize, sizeof(int));
		max[i] = calloc(arrSize, sizeof(int));
	}

	for (int i = 0; i < arrSize-1; i++)
	{        
		dp[i][i+1] = arr[i]*arr[i+1];
		max[i][i] = arr[i];
	}
	max[arrSize-1][arrSize-1] = arr[arrSize-1];

	for (int i = 0; i < arrSize; i++)
	{
		for (int j = i+1; j < arrSize; j++)
		{
			max[i][j] = (max[i][j-1] > arr[j] ? max[i][j-1] : arr[j]);
		}
	}

	for (int len = 2; len < arrSize; len++)
	{        
		for (int i = 0; i+len < arrSize; i++)
		{
			int end = i+len;
			for (int k = 0; k < len; k++)
			{
				int curK = i+k;
				int curRes = max[i][curK]*max[curK+1][end] + dp[i][curK] + dp[curK+1][end];
				if (dp[i][end] == 0)
				{
					dp[i][end] = curRes;
				} else
				{
					dp[i][end] = (dp[i][end] < curRes ? dp[i][end] : curRes);
				}
			}                                    
		}        
	}

	int ret = dp[0][arrSize-1];    
	for (int i = 0; i < arrSize; i++)
	{
		free(dp[i]);
		free(max[i]);
	}    
	free(dp);
	free(max);

	return ret;
}

