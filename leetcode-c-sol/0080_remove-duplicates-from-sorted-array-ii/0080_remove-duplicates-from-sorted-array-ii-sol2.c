int removeDuplicates(int* nums, int numsSize)
{
    int idx = 0;
    for (int i = 0; i < numsSize; i++) {
        if (i < 2 || nums[i] > nums[idx-2])
            nums[idx++] = nums[i];
    }
    return idx;
}
