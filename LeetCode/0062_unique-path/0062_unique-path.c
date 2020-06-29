
int uniquePaths(int m, int n)
{
    int **dp = malloc(sizeof(int *) * m);
    for (int i = 0; i < m; i++)
        dp[i] = malloc(sizeof(int) * n);

    for (int i = m - 1; i >= 0; i--)
        dp[i][n - 1] = 1;

    for (int j = n - 1; j >= 0; j--)
        dp[m - 1][j] = 1;

    for (int i = m - 2; i >= 0; i--)
        for (int j = n - 2; j >= 0; j--)
            dp[i][j] = dp[i + 1][j] + dp[i][j + 1];

    int ret = dp[0][0];
    for (int i = 0; i < m; i++)
        free(dp[i]);
    free(dp);
    return ret;
}
