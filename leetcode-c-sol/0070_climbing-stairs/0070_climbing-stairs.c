
int climbStairs(int n)
{
    if (n <= 2)
        return n;

    int *dp = malloc(sizeof(int) * (n + 1));
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];

    int ret = dp[n];
    free(dp);
    return ret;
}