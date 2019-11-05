#define MIN(a, b)   (a < b ? a : b)

int findCheapestPrice(int n, int** flights, int flightsSize, int* flightsColSize, int src, int dst, int K)
{
	int *dp = calloc(n,sizeof(int));
	int *pre = calloc(n, sizeof(int));

	// Init (K=0)
	for (int i = 0; i < flightsSize; i++)
	{
		if (src == flights[i][0])
		{                    
			dp[  flights[i][1] ] =  flights[i][2];
			pre[  flights[i][1] ] =  flights[i][2];
		}
	}

	// Start from "K=1"
	for (int x = 1; x < K+1; x++)
	{
		for (int i = 0; i < flightsSize; i++)
		{
			int u = flights[i][0];
			int v = flights[i][1];
			int w = flights[i][2];

			if (pre[u] != 0)
			{
				if (dp[v] == 0)
				{
					dp[v] = pre[u] + w;
				} else
				{
					dp[v] = MIN(dp[v], pre[u] + w);
				}
			}
		}

		memcpy(pre, dp, sizeof(int)*n);
	}

	int ret = dp[dst];
	free(dp);
	free(pre);
	return (ret == 0 ? -1 : ret);
}


