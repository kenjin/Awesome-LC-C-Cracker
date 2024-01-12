
#define MAX(a, b) (a > b ? a : b)

int rob(int* nums, int numsSize)
{
    if (numsSize == 1)
        return nums[0];
    else if (numsSize == 2)
        return MAX(nums[0], nums[1]);

    // include first element, loop to `nums[numsSize-2]` element to ignore the cycle to first element
    int dp0, dp1 = nums[0], dp2 = 0;
    int ret_in = MAX(dp1, dp2);
    for (int i = 2; i < numsSize-1; i++) {
        dp0 = dp1;
        dp1 = dp2;
        dp2 = nums[i] + MAX(dp0, dp1-nums[i-1]);
        ret_in = MAX(ret_in, dp2);
    }
    // exclude first element, loop to the end
    dp1 = 0, dp2 = nums[1];
    int ret_ex = MAX(dp1, dp2);
    for (int i = 2; i < numsSize; i++) {
        dp0 = dp1;
        dp1 = dp2;
        dp2 = nums[i] + MAX(dp0, dp1-nums[i-1]);
        ret_ex = MAX(ret_ex, dp2);
    }

    return MAX(ret_ex, ret_in);
}
