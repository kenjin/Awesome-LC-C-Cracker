int* getMaximumXor(int* nums, int numsSize, int maximumBit, int* returnSize)
{
    int k_target= (0x1 << maximumBit) - 1;
    int *ret = malloc(sizeof(int)*numsSize);
    *returnSize = numsSize;

    int xor_res = nums[0];
    for (int i = 1; i < numsSize; i++) {
        xor_res = xor_res ^ nums[i];
    }

    for (int i = 0; i < numsSize; i++) {
        ret[i] = xor_res ^ k_target;
        xor_res = xor_res ^ nums[numsSize - 1 - i];
    }

    return ret;
}
