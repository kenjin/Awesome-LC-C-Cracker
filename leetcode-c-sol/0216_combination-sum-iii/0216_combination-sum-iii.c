#define MALLOC_UNIT  (1500)
static bool backtrack(int target, int k, int cur, int*** ret, int* returnSize,
                      int** returnColumnSizes, int sum, int* tmp, int tmp_ctr) {
    if (tmp_ctr > k)
        return false;

    if (sum >= target) {
        if (sum == target && tmp_ctr == k) {
            if (!(*returnSize % MALLOC_UNIT)) {
                *ret = realloc(*ret, sizeof(int *)*(*returnSize + MALLOC_UNIT));
                *returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*(*returnSize + MALLOC_UNIT));
            }
            (*ret)[*returnSize] = malloc(sizeof(int) * k);
            (*returnColumnSizes)[*returnSize] = k;
            memcpy((*ret)[*returnSize], tmp, sizeof(int) * k);
            *returnSize += 1;
        }
        // Return true to indicade that we don't need to add later element
        // because sum is already >= target.
        return true;
    }

    for (int i = cur; i <= 9; i++) {
        tmp[tmp_ctr] = i;
        if (backtrack(target, k, i + 1, ret, returnSize,
                    returnColumnSizes, sum + i, tmp, tmp_ctr + 1))
            break;
    }
    return false;
}

int** combinationSum3(int k, int n, int* returnSize, int** returnColumnSizes)
{
    int* tmp = malloc(sizeof(int)*9);
    int** ret = malloc(sizeof(int*));
    *returnColumnSizes = malloc(sizeof(int));
    *returnSize = 0;
    backtrack(n, k, 1, &ret, returnSize, returnColumnSizes, 0, tmp, 0);
    free(tmp);
    ret = realloc(ret, sizeof(int *)*(*returnSize));
    *returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*(*returnSize));
    return ret;
}
