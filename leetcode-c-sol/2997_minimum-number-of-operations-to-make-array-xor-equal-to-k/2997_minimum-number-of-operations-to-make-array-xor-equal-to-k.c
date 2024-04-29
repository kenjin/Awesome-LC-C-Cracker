int minOperations(int* nums, int numsSize, int k)
{
    for (int i = 0; i < numsSize; i++)
        k ^= nums[i];

    int ret = 0;
    while (k) {
        ret += (k & 0x1);
        k >>= 1;
    }

    return ret;
}
