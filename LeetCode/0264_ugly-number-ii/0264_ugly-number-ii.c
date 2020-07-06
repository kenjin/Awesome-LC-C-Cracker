
#define MIN(a, b) (a < b ? a : b)

int nthUglyNumber(int n)
{
    if (n == 1)
        return 1;

    int *nums = malloc(sizeof(int) * n);
    nums[0] = 1;
    int mul2 = 0, mul3 = 0, mul5 = 0;
    for (int idx = 1; idx < n; idx++) {
        /* Get the min of ungly_num multiplied by 2/3/5 */
        int tmp = MIN(nums[mul2] * 2, MIN(nums[mul3] * 3, nums[mul5] * 5));
        if (tmp == nums[mul2] * 2)
            mul2++;
        if (tmp == nums[mul3] * 3)
            mul3++;
        if (tmp == nums[mul5] * 5)
            mul5++;

        nums[idx] = tmp;
    }

    int ret = nums[n - 1];
    free(nums);
    return ret;
}
