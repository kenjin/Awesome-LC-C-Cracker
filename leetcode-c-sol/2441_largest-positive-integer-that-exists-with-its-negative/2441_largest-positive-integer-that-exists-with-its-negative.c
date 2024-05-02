#define N_LEN (2001)

int findMaxK(int* nums, int numsSize)
{
    int ret = -1;
    char set[N_LEN] = {0};
    for (int i = 0; i < numsSize; i++) {
        set[nums[i] + 1000] = 1;
        if (set[nums[i]*(-1) + 1000]) {
            int cur = abs(nums[i]);
            if (ret == -1 || cur > ret)
                ret = cur;
        }
    }

    return ret;
}
