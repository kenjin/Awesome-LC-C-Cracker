
static inline int min3(int a, int b, int c)
{
    int tmp = (a < b ? a : b);
    return c < tmp ? c : tmp;
}

static int cal_max_square(int **matrix, int **dp, int row, int col)
{
    if (row == 0 || col == 0)
        return matrix[row][col];
    if (matrix[row][col] == 0)
        return 0;

    return min3(dp[row][col - 1], dp[row - 1][col], dp[row - 1][col - 1]) + 1;
}

int countSquares(int **matrix, int matrixSize, int *matrixColSize)
{
    int ret = 0;
    int col_size = matrixColSize[0];
    int min_side = matrixSize < col_size ? matrixSize : col_size;

    int **dp_square = malloc(sizeof(int *) * matrixSize);
    for (int i = 0; i < matrixSize; i++)
        dp_square[i] = calloc(col_size, sizeof(int));

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < col_size; j++) {
            int cal_res = cal_max_square(matrix, dp_square, i, j);
            dp_square[i][j] = cal_res;
            ret += cal_res;
        }
    }

    for (int i = 0; i < matrixSize; i++)
        free(dp_square[i]);
    free(dp_square);

    return ret;
}
