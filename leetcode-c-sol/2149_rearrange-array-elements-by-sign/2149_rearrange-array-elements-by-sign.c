/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rearrangeArray(int* nums, int numsSize, int* returnSize)
{
    int *ret = malloc(sizeof(int)*numsSize);
    int pos_idx = 0, neg_idx = 1;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0) {
            ret[pos_idx] = nums[i];
            pos_idx += 2;
            
        }
        else {
            ret[neg_idx] = nums[i];
            neg_idx += 2;
        }
    }
    *returnSize = numsSize;
    return ret;
}
