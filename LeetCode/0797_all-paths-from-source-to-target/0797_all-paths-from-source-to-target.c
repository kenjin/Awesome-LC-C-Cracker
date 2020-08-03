LLOC_UNIT_SZ 500

    static void
    dfs(int **graph,
        int *tmp,
        char *chk,
        int tmp_ctr,
        int idx,
        int graph_sz,
        int *graph_col_sz,
        int ***ret,
        int *ret_sz,
        int **ret_col_sz)
{
    tmp[tmp_ctr] = idx;
    if (idx == graph_sz - 1) {
        /* Update the result */
        if (*ret_sz % ALLOC_UNIT_SZ == 0) {
            *ret = realloc(*ret, sizeof(int *) * (*ret_sz + ALLOC_UNIT_SZ));
            *ret_col_sz =
                realloc(*ret_col_sz, sizeof(int) * (*ret_sz + ALLOC_UNIT_SZ));
        }

        (*ret)[*ret_sz] = malloc(sizeof(int) * (tmp_ctr + 1));
        memcpy((*ret)[*ret_sz], tmp, sizeof(int) * (tmp_ctr + 1));
        (*ret_col_sz)[*ret_sz] = tmp_ctr + 1;
        *ret_sz += 1;
        return;
    }

    for (int x = 0; x < graph_col_sz[idx]; x++) {
        int cur_idx = graph[idx][x];
        if (!chk[cur_idx]) {
            chk[cur_idx] = 1;
            dfs(graph, tmp, chk, tmp_ctr + 1, cur_idx, graph_sz, graph_col_sz,
                ret, ret_sz, ret_col_sz);
        }

        chk[cur_idx] = 0;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **allPathsSourceTarget(int **graph,
                           int graph_sz,
                           int *graph_col_sz,
                           int *ret_sz,
                           int **ret_col_sz)
{
    int *tmp = malloc(sizeof(int) * graph_sz);
    char *chk = calloc(graph_sz, sizeof(char));

    int **ret = malloc(sizeof(int *));
    *ret_col_sz = malloc(sizeof(int));
    *ret_sz = 0;
    dfs(graph, tmp, chk, 0, 0, graph_sz, graph_col_sz, &ret, ret_sz,
        ret_col_sz);

    free(chk);
    free(tmp);
    return ret;
}
