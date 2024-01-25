
#define REALLOC_UNIT    (5000)
static void non_decreasing_subseq_builder(int *nums, int nums_sz, int cur_idx, int *tmp, int tmp_idx, int ***ret, int *returnSize, int **returnColumnSizes)
{
    if (tmp_idx >= 2) {
        if (*returnSize % REALLOC_UNIT == 0) {
            *ret = realloc(*ret, sizeof(int*)*(*returnSize + REALLOC_UNIT));
            *returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*(*returnSize + REALLOC_UNIT));
        }
        (*ret)[*returnSize] = malloc(sizeof(int)*tmp_idx);
        memcpy((*ret)[*returnSize], tmp, sizeof(int)*tmp_idx);
        (*returnColumnSizes)[*returnSize] = tmp_idx;
        *returnSize += 1;
    }
    // use set[] to avoid the duplicate in same level, shift 100 to store the value
    // (-100 <= nums[i] <= 100)
    char set[201] = {0}; //
    for (int i = cur_idx; i < nums_sz; i++) {
        if ((tmp_idx > 0 && tmp[tmp_idx-1] > nums[i]) || set[nums[i] + 100])
            continue;
        set[nums[i] + 100] = 1; 
        tmp[tmp_idx] = nums[i];
        non_decreasing_subseq_builder(nums, nums_sz, i + 1, tmp, tmp_idx+1, ret, returnSize, returnColumnSizes);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findSubsequences(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    int **ret = malloc(sizeof(int *));
    *returnColumnSizes = malloc(sizeof(int));
    *returnSize = 0;
    int *tmp = malloc(sizeof(int)*numsSize);
    non_decreasing_subseq_builder(nums, numsSize, 0, tmp, 0, &ret, returnSize, returnColumnSizes);
    free(tmp);
    return ret;  
}
