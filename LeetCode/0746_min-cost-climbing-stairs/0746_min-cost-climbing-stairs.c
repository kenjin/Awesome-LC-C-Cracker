
#define MIN(a, b) (a < b ? a : b)
int minCostClimbingStairs(int* cost, int costSize)
{
    int *dp = calloc(costSize, sizeof(int));
    
    dp[0] = cost[0];
    dp[1] = cost[1];    
    for (int i = 2; i < costSize; i++)
    {
        dp[i] = MIN(dp[i-1], dp[i-2]) + cost[i];
    }
    
    int ret = MIN(dp[costSize-1], dp[costSize-2]);
    free(dp);
    return ret;
}

