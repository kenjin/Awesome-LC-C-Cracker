int* singleNumber(int* nums, int numsSize, int* returnSize)
{
    int val = 0;
    for (int i = 0; i < numsSize; i++)
        val ^= nums[i];

    // !!! Casting to unsigned to safely handle negation !!!
    unsigned int u_val = (unsigned int)val;
    int low_b = u_val & -u_val;
    int *ret = calloc(2, sizeof(int));
    *returnSize = 2;
    for (int i = 0; i < numsSize; i++) {
        if (low_b & nums[i])
            ret[0] ^= nums[i];
        else
            ret[1] ^= nums[i];
    }

    return ret;    
}
