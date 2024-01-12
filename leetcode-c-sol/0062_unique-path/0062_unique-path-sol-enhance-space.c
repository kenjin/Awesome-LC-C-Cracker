
int uniquePaths(int m, int n)
{
    int *dp = malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
        dp[i] = 1;

    for (int x = 1; x < m; x++) {
        dp[0] = 1;
        for (int i = 1; i < n; i++)
            dp[i] = dp[i-1] + dp[i];
    }
    int ret = dp[n-1];
    free(dp);
    return ret;
}
