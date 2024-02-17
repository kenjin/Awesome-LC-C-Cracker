/***
Approach: DP

Similar to #123, except now it's up to k transactions. From the recurrence
formula of #123, we can see that the state transition equations for odd and even
rows are regular, namely:

For odd rows (i is odd):
dp[i][j] = max(dp[i][ j - 1], dp[i - 1][j - 1] - prices[j]);

For even rows (i is even):
dp[i][j] = max(dp[i][ j - 1], dp[i - 1][j - 1] + prices[j]);

Regarding the initialization of the dp array: except for the first row (which is
all 0), there's a pattern for dp[i][0] based on whether i is odd or even. When i
is odd, it's initialized as -prices[0], and when i is even, it's initialized as
0.

***/

#define MAX(a, b) (a > b ? a : b)
int maxProfit(int k, int* prices, int pricesSize) {
    int** dp = malloc(sizeof(int*) * (1 + (k << 1)));
    for (int i = 0; i < (1 + (k << 1)); i++)
        dp[i] = calloc(pricesSize, sizeof(int));

    for (int i = 1; i < (1 + (k << 1)); i += 2)
        dp[i][0] = -prices[0];

    for (int i = 1; i < pricesSize; i++) {

        for (int kidx = 1; kidx < (1 + (k << 1)); kidx++) {
            if (kidx & 0x1)
                dp[kidx][i] =
                    MAX(dp[kidx][i - 1], dp[kidx - 1][i - 1] - prices[i]);
            else
                dp[kidx][i] =
                    MAX(dp[kidx][i - 1], dp[kidx - 1][i - 1] + prices[i]);
        }
    }

    int ret = dp[(k << 1)][pricesSize - 1];
    for (int i = 0; i < (1 + (k << 1)); i++)
        free(dp[i]);
    free(dp);
    return ret;
}
