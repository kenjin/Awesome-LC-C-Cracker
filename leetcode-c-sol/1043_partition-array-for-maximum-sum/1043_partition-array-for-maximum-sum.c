
#define MAX(a, b) (a > b ? a : b)
int maxSumAfterPartitioning(int* arr, int arrSize, int k)
{
    int* dp = calloc((arrSize + 1), sizeof(int));
    for (int i = 1; i <= arrSize; i++) {
        int cur_max = -1;
        for (int j = 1; j <= k && i - j >= 0; j++) {
            cur_max = MAX(cur_max, arr[i - j]);
            dp[i] = MAX(dp[i], (dp[i - j] + cur_max * j));
        }
    }

    int ret = dp[arrSize];
    free(dp);
    return ret;
}
