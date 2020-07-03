
static int compare(void *a, void *b)
{
    return *(int *) a - *(int *) b;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *largestDivisibleSubset(int *nums, int nums_sz, int *return_sz)
{
    if (!nums_sz) {
        *return_sz = 0;
        return NULL;
    }

    qsort(nums, nums_sz, sizeof(int), compare);
    int *dp = calloc(nums_sz, sizeof(int));
    int *record = calloc(nums_sz, sizeof(int));
    int max_idx = 0, max = 0;
    for (int divisor = nums_sz - 1; divisor >= 0; divisor--) {
        for (int dividend = divisor; dividend < nums_sz; dividend++) {
            if (nums[dividend] % nums[divisor] == 0 &&
                dp[divisor] < dp[dividend] + 1) {
                dp[divisor] = dp[dividend] + 1;
                record[divisor] = dividend;
                if (max < dp[divisor]) {
                    max = dp[divisor];
                    max_idx = divisor;
                }
            }
        }
    }

    int *ret = malloc(sizeof(int) * max);
    *return_sz = max;
    for (int i = 0; i < max; i++) {
        ret[i] = nums[max_idx];
        max_idx = record[max_idx];
    }

    free(dp);
    free(record);
    return ret;
}
