static void dfs_handler(int* nums, int cur, int num_sz, int *tmp, int tmp_ctr, int **ret, int *ret_sz, int *ret_col_sz)
{
    if (cur == num_sz) {
        int *res = malloc(sizeof(int)*tmp_ctr);
        memcpy(res, tmp, sizeof(int)*tmp_ctr);
        ret[*ret_sz] = res;
        ret_col_sz[*ret_sz] = tmp_ctr;
        (*ret_sz)++;
        return;
    }

    dfs_handler(nums, cur + 1, num_sz, tmp, tmp_ctr, ret, ret_sz, ret_col_sz);
    tmp[tmp_ctr] = nums[cur];
    dfs_handler(nums, cur + 1, num_sz, tmp, tmp_ctr + 1, ret, ret_sz, ret_col_sz);
}

int** subsets(int* nums, int num_sz, int* ret_sz, int** ret_col_sz)
{
    int *tmp = malloc(sizeof(int)*num_sz);
    int **ret = malloc(sizeof(int*)*(1 << num_sz));
    *ret_col_sz = malloc(sizeof(int)*(1 << num_sz));
    *ret_sz = 0;
    dfs_handler(nums, 0, num_sz, tmp, 0, ret, ret_sz, *ret_col_sz);

    free(tmp);
    return ret;
}
