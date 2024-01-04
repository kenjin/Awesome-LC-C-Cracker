#define MAX(a, b) (a > b ? a : b)
int max_sub_helper(int *nums, int head, int tail)
{
    if (head == tail)
        return nums[head];

    int mid = head + ((tail-head) >> 1);
    int max_sum_l = INT_MIN, max_sum_r = INT_MIN, tmp_sum = 0;
    for (int i = mid; i >= head; i--) {
        tmp_sum += nums[i];
        max_sum_l = MAX(tmp_sum, max_sum_l);
    }

    tmp_sum = 0;
    for (int i = mid + 1; i <= tail; i++) {
        tmp_sum += nums[i];
        max_sum_r = MAX(tmp_sum, max_sum_r);
    }

    int sub_l = max_sub_helper(nums, head, mid);
    int sub_r = max_sub_helper(nums, mid + 1, tail);

    int ret = MAX(sub_l, sub_r);
    ret = MAX(ret, max_sum_l+max_sum_r);
    return ret;
}

int maxSubArray(int* nums, int numsSize)
{
    return max_sub_helper(nums, 0, numsSize - 1);
}
