#define MIN(a, b) (a < b ? a : b)
int coinChange(int* coins, int coinsSize, int amount)
{
    int *dp = calloc(amount + 1, sizeof(int));
    dp[0] = 0;
    for (int i = 1; i <= amount; i++)
        dp[i] = amount + 1;

    for (int x = 1; x <= amount; x++) {
        for (int i = 0; i < coinsSize; i++) {
            if (coins[i] <= x)
                dp[x] = MIN(dp[x], dp[x - coins[i]] + 1);
        }
    }
    return (dp[amount] > amount ? -1 : dp[amount]);
}
