
#define MAX(a, b) (a > b ? a : b)
#define MIN3(a, b, c) (a < b ? (a < c ? a : c) : (b < c ? b : c))

int maximalSquare(char **matrix, int matrix_rsz, int *matrix_csz)
{
    if (!matrix_rsz)
        return 0;
    int **dp = malloc(sizeof(int *) * matrix_rsz);
    int ret = 0, col_sz = matrix_csz[0];
    for (int i = 0; i < matrix_rsz; i++) {
        dp[i] = calloc(col_sz, sizeof(int));
        if (matrix[i][0] == '1') {
            dp[i][0] = 1;
            ret = 1;
        }
    }

    for (int i = 1; i < col_sz; i++) {
        if (matrix[0][i] == '1') {
            dp[0][i] = 1;
            ret = 1;
        }
    }

    for (int i = 1; i < matrix_rsz; i++) {
        for (int j = 1; j < col_sz; j++) {
            if (matrix[i][j] == '1')
                dp[i][j] =
                    MIN3(dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]) + 1;
            ret = MAX(dp[i][j], ret);
        }
    }

    for (int i = 0; i < matrix_rsz; i++)
        free(dp[i]);
    free(dp);

    return ret * ret;
}