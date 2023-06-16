typedef struct __record {
    int num;
    int dup;
} REC;

static int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

#define MALLOC_UNIT 500

static void dfs(REC *r,
                int *tmp,
                int tmp_sz,
                int cur,
                int r_sz,
                int ***ret,
                int *ret_sz,
                int **ret_col_sz)
{
    if (cur == r_sz) {
        if (*ret_sz % MALLOC_UNIT == 0) {
            *ret = realloc(*ret, sizeof(int *) * (*ret_sz + MALLOC_UNIT));
            *ret_col_sz =
                realloc(*ret_col_sz, sizeof(int) * (*ret_sz + MALLOC_UNIT));
        }

        if (!tmp_sz) {
            (*ret)[*ret_sz] = NULL;
            (*ret_col_sz)[*ret_sz] = 0;
        } else {
            (*ret)[*ret_sz] = malloc(sizeof(int) * tmp_sz);
            (*ret_col_sz)[*ret_sz] = tmp_sz;
            memcpy((*ret)[*ret_sz], tmp, sizeof(int) * tmp_sz);
        }
        *ret_sz += 1;
        return;
    }
    /* don't select this element */
    dfs(r, tmp, tmp_sz, cur + 1, r_sz, ret, ret_sz, ret_col_sz);
    /* select and consider the duplicates */
    for (int i = 1; i <= r[cur].dup; i++) {
        tmp[tmp_sz++] = r[cur].num;
        dfs(r, tmp, tmp_sz, cur + 1, r_sz, ret, ret_sz, ret_col_sz);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **subsetsWithDup(int *nums, int nums_sz, int *ret_sz, int **ret_col_sz)
{
    qsort(nums, nums_sz, sizeof(int), compare);

    REC *r = malloc(sizeof(REC) * nums_sz);
    int cur = -1;
    for (int i = 0; i < nums_sz; i++) {
        if (i == 0 || nums[i] != nums[i - 1]) {
            cur++;
            r[cur].num = nums[i];
            r[cur].dup = 1;
            continue;
        }
        r[cur].dup += 1;
    }

    int *tmp = malloc(sizeof(int) * nums_sz);
    int **ret = malloc(sizeof(int *));
    *ret_col_sz = malloc(sizeof(int));
    *ret_sz = 0;
    dfs(r, tmp, 0, 0, cur + 1, &ret, ret_sz, ret_col_sz);
    free(tmp);
    free(r);
    return ret;
}
