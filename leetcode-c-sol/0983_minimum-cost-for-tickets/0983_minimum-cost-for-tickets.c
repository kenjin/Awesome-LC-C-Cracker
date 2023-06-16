

#define MIN(a, b) (a < b ? a : b)
int mincostTickets(int *days, int days_sz, int *costs, int costs_sz)
{
    int last_d = days[days_sz - 1];
    int *dp = malloc(sizeof(int) * (last_d + 1));
    for (int i = 0; i <= last_d; i++)
        dp[i] = INT_MAX;

    for (int i = 0; i < days_sz; i++)
        dp[days[i]] = 0;

    dp[0] = 0;
    for (int i = 1; i <= last_d; i++) {
        if (!dp[i]) {
            int cur = dp[i - 1] + costs[0];
            int d7_idx = (i - 7 > 0 ? i - 7 : 0);
            int d30_idx = (i - 30 > 0 ? i - 30 : 0);
            cur = MIN(cur, dp[d7_idx] + costs[1]);
            cur = MIN(cur, dp[d30_idx] + costs[2]);
            dp[i] = cur;
        } else {
            dp[i] = dp[i - 1];
        }
    }

    int ret = dp[last_d];
    free(dp);
    return ret;
}