long long countSubarrays(int* nums, int numsSize, int k) {
    int head = 0, max = 0, ctr = 0;
    long long ret = 0;
    for (int i = 0; i < numsSize; i++)
        max = (max > nums[i] ? max : nums[i]);

    for (int tail = 0; tail < numsSize; tail++) {
        ctr += (nums[tail] == max ? 1 : 0);
        while (ctr >= k) {
            ret += (numsSize - tail);
            ctr -= (nums[head++] == max ? 1 : 0);
        }
    }
    return ret;
}
