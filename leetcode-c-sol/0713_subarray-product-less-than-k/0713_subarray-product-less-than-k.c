int numSubarrayProductLessThanK(int* nums, int numsSize, int k)
{
    int prod_res = 1, head = 0, ret = 0;
    for (int tail = 0; tail < numsSize; tail++) {
        // Check the largest window size to satisfy that the subarray product is
        // less than k.
        prod_res *= nums[tail];
        while (prod_res >= k && head <= tail) {
            prod_res /= nums[head];
            head++;
        }
        ret += (tail - head + 1);
    }
    return ret;
}

