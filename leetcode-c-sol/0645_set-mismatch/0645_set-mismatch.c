/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findErrorNums(int* nums, int numsSize, int* returnSize)
{
    int *set = calloc(numsSize, sizeof(int));
    for (int i = 0; i < numsSize; i++)
        set[nums[i]-1]++;

    int *ret = malloc(sizeof(int)*2);
    *returnSize =2;
    for (int i = 0; i < numsSize; i++) {
        if (set[i] == 2)
            ret[0] = i + 1;
        else if (set[i] == 0)
            ret[1] = i + 1;
    }

    return ret;
}
