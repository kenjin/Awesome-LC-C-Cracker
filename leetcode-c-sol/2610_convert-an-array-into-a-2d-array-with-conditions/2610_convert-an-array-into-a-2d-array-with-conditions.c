/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#define MAX_NUMS_LEN (200)

int** findMatrix(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    int nums_ctr[MAX_NUMS_LEN + 1] = {0};
    *returnSize = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums_ctr[nums[i]] == 0)
            nums_ctr[0]++; // use [0] element to record total diff nums for allocating column size

        nums_ctr[nums[i]]++;
        if (nums_ctr[nums[i]] > *returnSize)
            *returnSize = nums_ctr[nums[i]];
    }

    int **ret = malloc(sizeof(int*) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        ret[i] = malloc(sizeof(int)*(nums_ctr[0]));
    }
    *returnColumnSizes = calloc(*returnSize, sizeof(int));
    for (int i = 1; i <= MAX_NUMS_LEN; i++) {
        for (int x = 0; x < nums_ctr[i]; x++) {
            ret[x][(*returnColumnSizes)[x]] = i;
            (*returnColumnSizes)[x]++;
        }
    }
    return ret;
}
