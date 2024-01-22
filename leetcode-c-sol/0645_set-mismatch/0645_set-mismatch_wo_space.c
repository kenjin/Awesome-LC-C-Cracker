/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findErrorNums(int* nums, int numsSize, int* returnSize)
{
    int *ret = malloc(sizeof(int)*2);
    *returnSize = 2;
    // Iterate nums and change the expected position to its opposite number. 
    // If the element already becomes negative, it indicates that it is a duplicate.
    for (int i = 0; i < numsSize; i++) {
        int cur_idx = abs(nums[i]);

        if (nums[cur_idx-1] < 0) 
            ret[0] = cur_idx;
        if (nums[cur_idx-1] > 0) 
            nums[cur_idx-1] *= -1;
    }
    // If a certain position is positive, it means that the corresponding number has not appeared before.
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0)
            ret[1] = i + 1;
    }

    return ret;
}
