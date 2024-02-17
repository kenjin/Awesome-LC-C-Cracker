/***
Approach: DP

Since we can complete at most 2 transactions, we can divide the trading process
into 5 states:

dp[0][i]: The maximum cash when no operation is performed on the i-th day (can
be understood as the state of never purchasing stocks). dp[1][i]: The maximum
cash when buying stocks for the first time on the i-th day, or holding stocks
continuously after the first purchase. dp[2][i]: The maximum cash when selling
stocks for the first time on the i-th day, or not holding stocks after the first
sale. dp[3][i]: The maximum cash when buying stocks for the second time on the
i-th day, or holding stocks continuously after the second purchase. dp[4][i]:
The maximum cash when selling stocks for the second time on the i-th day, or not
holding stocks after the second sale.

dp[1][i] can be derived from dp[1][i-1] (the state of holding stocks
continuously after the i-1th day's first purchase) and dp[0][i-1] (the state of
never purchasing stocks).
=> dp[1][i] = max(dp[1][i - 1], dp[0][i - 1] - prices[i]);

dp[2][i] can be derived from dp[2][i-1] (the state of not holding stocks after
the i-1th day's first sale) and dp[1][i-1].
=> dp[2][i] = max(dp[2][i - 1], dp[1][i - 1] + prices[i]);

Similarly, state transition equations for dp[3][i] is similar to dp[1][i] and
dp[4][i] similar to dp[2][i].

Regarding the initialization of the dp array:
- dp[0][i] are obviously all 0 because there is no cash when no operation is
performed;
- dp[2][0] and dp[4][0] should be 0 because on the 0th day, doing nothing surely
holds the maximum cash of 0.
- dp[1][0] and dp[3][0] should be initialized as -prices[i]
(About dp[3][0], it can be considered that on the 0th day, the first purchase
and sale are made, and then a second purchase is made, so it should be
initialized as -prices[i].)

***/

#define MAX(a, b) (a > b ? a : b)
int maxProfit(int* prices, int pricesSize) {
    int** dp = malloc(sizeof(int*) * 5);
    for (int i = 0; i < 5; i++)
        dp[i] = calloc(pricesSize, sizeof(int));

    dp[1][0] = -prices[0];
    dp[3][0] = -prices[0];
    for (int i = 1; i < pricesSize; i++) {
        dp[1][i] = MAX(dp[1][i - 1], dp[0][i - 1] - prices[i]);
        dp[2][i] = MAX(dp[2][i - 1], dp[1][i - 1] + prices[i]);
        dp[3][i] = MAX(dp[3][i - 1], dp[2][i - 1] - prices[i]);
        dp[4][i] = MAX(dp[4][i - 1], dp[3][i - 1] + prices[i]);
    }

    int ret = dp[4][pricesSize - 1];
    for (int i = 0; i < 5; i++)
        free(dp[i]);
    free(dp);
    return ret;
}
