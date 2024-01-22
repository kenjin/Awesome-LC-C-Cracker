/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

static void dfs_runner(int* nums, int numsSize, int *tmp, int tmp_idx, char *v, int **ret, int* returnSize, int** returnColumnSizes)
{
    if (tmp_idx == numsSize) {
        ret[*returnSize] = malloc(sizeof(int)*numsSize);
        memcpy(ret[*returnSize], tmp, sizeof(int)*numsSize);
        (*returnColumnSizes)[*returnSize] = numsSize;
        *returnSize += 1;
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        if (v[i] || (i > 0 && nums[i] == nums[i-1] && !v[i-1]))
            continue;
        v[i] = 1;
        tmp[tmp_idx] = nums[i];
        dfs_runner(nums, numsSize, tmp, tmp_idx + 1, v, ret, returnSize, returnColumnSizes);
        v[i] = 0;
    }
}

static int compare(const void *a, const void *b)
{
    return (*(int*)a) - (*(int*)b);
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    qsort(nums, numsSize, sizeof(int), compare);
    int max_per = 1;
    for (int i = 2; i <= numsSize; i++)
        max_per *= i;

    int **ret = malloc(sizeof(int*)*max_per);
    *returnColumnSizes = malloc(sizeof(int)*max_per);
    int *tmp = malloc(sizeof(int)*numsSize);
    char *visited = calloc(numsSize, sizeof(int));
    *returnSize = 0;
    dfs_runner(nums, numsSize, tmp, 0, visited, ret, returnSize, returnColumnSizes);
    free(visited);
    return ret;
}
