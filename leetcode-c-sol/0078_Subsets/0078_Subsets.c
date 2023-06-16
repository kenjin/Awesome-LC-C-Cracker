/**
  78. Subsets [M]
Ref: https://leetcode.com/problems/subsets/

Given a set of distinct integers, nums, return all possible subsets (the power
set).

Note: The solution set must not contain duplicate subsets.

Example:
Input: nums = [1,2,3]
Output:
[
[3],
[1],
[2],
[1,2,3],
[1,3],
[2,3],
[1,2],
[]
]

 */
#define MALLOC_UNIT 500

static void dfs(int *nums,
                int *tmp,
                int tmp_sz,
                int cur,
                int nums_sz,
                int ***ret,
                int *ret_sz,
                int **ret_col_sz)
{
    if (cur == nums_sz) {
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

    tmp[tmp_sz] = nums[cur];
    dfs(nums, tmp, tmp_sz + 1, cur + 1, nums_sz, ret, ret_sz, ret_col_sz);
    dfs(nums, tmp, tmp_sz, cur + 1, nums_sz, ret, ret_sz, ret_col_sz);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **subsets(int *nums, int nums_sz, int *ret_sz, int **ret_col_sz)
{
    int *tmp = malloc(sizeof(int) * nums_sz);
    int **ret = malloc(sizeof(int *));
    *ret_col_sz = malloc(sizeof(int));
    *ret_sz = 0;
    dfs(nums, tmp, 0, 0, nums_sz, &ret, ret_sz, ret_col_sz);
    free(tmp);

    return ret;
}
