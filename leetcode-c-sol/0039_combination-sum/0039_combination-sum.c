
#define MAX_COMBINATIONS (150)
static bool backtrack(int target, int cur_idx, int* candidates,
                      int candidatesSize, int*** ret, int* returnSize,
                      int** returnColumnSizes, int sum, int* tmp, int tmp_ctr) {
    if (sum >= target) {
        if (sum == target) {
            (*ret)[*returnSize] = malloc(sizeof(int) * tmp_ctr);
            (*returnColumnSizes)[*returnSize] = tmp_ctr;
            memcpy((*ret)[*returnSize], tmp, sizeof(int) * tmp_ctr);
            *returnSize += 1;
        }
        // Return true to indicade that we don't need to add later element
        // because sum is already >= target.
        return true;
    }

    for (int i = cur_idx; i < candidatesSize; i++) {
        tmp[tmp_ctr] = candidates[i];
        if (backtrack(target, i, candidates, candidatesSize, ret, returnSize,
                      returnColumnSizes, sum + candidates[i], tmp, tmp_ctr + 1))
            break;
    }
    return false;
}

static int compare(const void* a, const void* b) { return *(int*)a - *(int*)b; }

int** combinationSum(int* candidates, int candidatesSize, int target,
                     int* returnSize, int** returnColumnSizes) {
    qsort(candidates, candidatesSize, sizeof(int), compare);
    int max_sz = target / candidates[0] + 1;
    int* tmp = malloc(sizeof(int) * max_sz);
    int** ret = malloc(sizeof(int*) * MAX_COMBINATIONS);
    *returnColumnSizes = malloc(sizeof(int) * MAX_COMBINATIONS);
    *returnSize = 0;
    backtrack(target, 0, candidates, candidatesSize, &ret, returnSize,
              returnColumnSizes, 0, tmp, 0);
    free(tmp);
    return ret;
}

