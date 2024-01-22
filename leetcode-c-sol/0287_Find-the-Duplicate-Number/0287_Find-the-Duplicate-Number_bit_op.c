int findDuplicate(int* nums, int numsSize)
{ 
    int ret = 0;
    for (int i = 0; i < 32; i++) {
        int mask = ((unsigned int)0x1 << i), a = 0, b = 0;
        for (int x = 0; x < numsSize; x++) {
            a += ((nums[x] & mask) ? 1 : 0);
            b += ((x & mask) ? 1 : 0);
        }

        if (a > b)
            ret |= mask;
    }
    return ret;
}
