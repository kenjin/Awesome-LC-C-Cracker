int *productExceptSelf(int *nums, int nums_sz, int *ret_sz)
{
    int *ret = calloc(nums_sz, sizeof(int));
    *ret_sz = nums_sz;

    for (int i = 0; i < nums_sz; i++)
        ret[i] = (i == 0 ? 1 : ret[i - 1] * nums[i - 1]);

    int last = 0;
    for (int i = nums_sz - 1; i >= 0; i--) {
        last = (i == nums_sz - 1 ? 1 : last * nums[i + 1]);
        ret[i] = ret[i] * last;
    }
    return ret;
}