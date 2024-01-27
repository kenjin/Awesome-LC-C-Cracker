int kInversePairs(int n, int k)
{
    // dp[n][k] = dp[n][k-1] + dp[n - 1][k] - dp[n - 1][k - n]
    int **dp = malloc(sizeof(int*)*(n+1));
    for (int i = 0; i <= n; i++) {
        dp[i] = calloc((k+1), sizeof(int));
    }

    int mod = 1000000007;
    dp[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            for (int m = 0; m <= k; m++) {
                if (m - j >= 0 && m - j <= k)
                    dp[i][m] = (dp[i][m] + dp[i - 1][m - j]) % mod;
            }
        }
    }
    int ret = dp[n][k];
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    return ret;
}

