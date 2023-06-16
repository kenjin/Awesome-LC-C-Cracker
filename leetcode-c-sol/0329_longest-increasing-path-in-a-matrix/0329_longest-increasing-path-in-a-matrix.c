static int dfs(int **matrix, int **dp, int row_sz, int col_sz, int x, int y)
{
    if (dp[x][y])
        return dp[x][y];

    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int max = 1;
    for (int i = 0; i < 4; i++) {
        int cur_x = x + dir[i][0], cur_y = y + dir[i][1];
        if (cur_x >= 0 && cur_x < row_sz && cur_y >= 0 && cur_y < col_sz &&
            matrix[x][y] < matrix[cur_x][cur_y]) {
            int len = 1 + dfs(matrix, dp, row_sz, col_sz, cur_x, cur_y);
            max = (max > len ? max : len);
        }
    }
    dp[x][y] = max;
    return max;
}

int longestIncreasingPath(int **matrix, int matrix_sz, int *matrix_col_sz)
{
    if (!matrix_sz)
        return 0;

    int **dp = malloc(sizeof(int *) * matrix_sz);
    int m_col_sz = matrix_col_sz[0];
    for (int i = 0; i < matrix_sz; i++)
        dp[i] = calloc(m_col_sz, sizeof(int));

    int ret = 1;
    for (int i = 0; i < matrix_sz; i++) {
        for (int j = 0; j < m_col_sz; j++) {
            int tmp = dfs(matrix, dp, matrix_sz, m_col_sz, i, j);
            ret = (ret > tmp ? ret : tmp);
        }
    }

    for (int i = 0; i < matrix_sz; i++)
        free(dp[i]);
    free(dp);
    return ret;
}
