int wiggleMaxLength(int* nums, int numsSize)
{
    int pre_diff = 0, ret = 1;
    for (int i = 0; i < numsSize-1; i++) {
        int cur_diff = nums[i+1] - nums[i];
        if (cur_diff > 0 && pre_diff <= 0 || cur_diff < 0 && pre_diff >= 0) {
            pre_diff = cur_diff;
            ret++;
        }
    }
    return ret;
}

