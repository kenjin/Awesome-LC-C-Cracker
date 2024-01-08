int numberOfArithmeticSlices(int* nums, int numsSize)
{
    if (numsSize < 3)
        return 0;

    int len = 2, ret = 0;
    for (int i = 2; i < numsSize; i++) {
        if (nums[i] - nums[i-1] == nums[i-1] - nums[i-2]) {
            len++;
        } else {
            if (len > 2)
                ret += (((len-1) * (len-2)) >> 1);
            len = 2;
        }
    }
    if (len > 2)
        ret += (((len-1) * (len-2)) >> 1);

    return ret;
}
