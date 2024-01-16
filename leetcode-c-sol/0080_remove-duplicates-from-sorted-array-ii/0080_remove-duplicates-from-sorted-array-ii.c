int removeDuplicates(int* nums, int numsSize)
{
    int dup = 0, idx = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[idx]) {
            nums[++idx] = nums[i];
            dup = 0;
        } else {
            // one chance
            if (dup == 0) {
                nums[++idx] = nums[i];
                dup++;
            }
        }
    }
    return idx + 1;
}
