
#define MAX(a, b) (a > b ? a : b)

int rob(int* nums, int numsSize) 
{
    /**
     * dp  = best amount in i days
     * dp1 = best amount in "i-1" days
     * dp2 = best amount in "i-2" days
     */
    int dp1 = 0, dp2 = 0, dp;
    for (int i = 0; i < numsSize; i++) {
        dp = MAX(dp2 + nums[i], dp1);
        dp2 = dp1;
        dp1 = dp;
    }
    return dp1;
}
