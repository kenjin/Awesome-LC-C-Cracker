int subsetXORSum(int* nums, int numsSize) {
    int bit_mask = 0;
    for (int i = 0; i < numsSize; i++)
        bit_mask |= nums[i];
    return bit_mask * (1 << (numsSize - 1));
}
