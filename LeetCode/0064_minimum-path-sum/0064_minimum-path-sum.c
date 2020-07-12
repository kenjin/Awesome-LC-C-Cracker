
#define MIN(a, b) (a < b ? a : b)

int minPathSum(int **grid, int grid_sz, int *grid_col_sz)
{
    /* sanity check */
    if (grid_sz == 0)
        return 0;

    int **dp = malloc(sizeof(int *) * grid_sz);
    int col_sz = grid_col_sz[0], sum = 0;
    for (int i = 0; i < grid_sz; i++) {
        dp[i] = malloc(sizeof(int) * col_sz);
        sum += grid[i][0];
        dp[i][0] = sum;
    }
    sum = 0;
    for (int i = 0; i < col_sz; i++) {
        sum += grid[0][i];
        dp[0][i] = sum;
    }

    for (int i = 1; i < grid_sz; i++) {
        for (int j = 1; j < col_sz; j++)
            dp[i][j] = MIN(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
    }

    int ret = dp[grid_sz - 1][col_sz - 1];
    for (int i = 0; i < grid_sz; i++)
        free(dp[i]);
    free(dp);

    return ret;
}