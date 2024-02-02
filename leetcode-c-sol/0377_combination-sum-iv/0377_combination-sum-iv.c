int combinationSum4(int* nums, int numsSize, int target) {
    int dp[1001] = {0};
    dp[0] = 1;
    for (int i = 1; i <= target; i++) {
        for (int x = 0; x < numsSize; x++) {
            if (nums[x] <= i && dp[i] < INT_MAX - dp[i - nums[x]]) {
                dp[i] += dp[i - nums[x]];
            }
        }
    }

    return dp[target];
}
