/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */

static bool backtrack(int n, int cur, int pick, int k, int** ret, int* ret_sz,
                      int* ret_col_sz, int* tmp) {
    if (pick > k)
        return false;

    if (pick == k) {
        ret[*ret_sz] = malloc(sizeof(int) * k);
        ret_col_sz[*ret_sz] = k;
        memcpy(ret[*ret_sz], tmp, sizeof(int) * k);
        *ret_sz += 1;
        return true;
    }

    for (int i = cur; i <= n; i++) {
        tmp[pick] = i;
        if (!backtrack(n, i + 1, pick + 1, k, ret, ret_sz, ret_col_sz, tmp))
            break;
    }
    return true;
}

int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
    int sz = 1, d = 1;
    for (int i = 0; i < k; i++) {
        sz *= (n - i);
        sz /= (i + 1);
    }

    int** ret = malloc(sizeof(int*) * sz);
    *returnColumnSizes = malloc(sizeof(int) * sz);
    *returnSize = 0;
    int* tmp = malloc(sizeof(int) * k);
    backtrack(n, 1, 0, k, ret, returnSize, *returnColumnSizes, tmp);
    free(tmp);
    return ret;
}
