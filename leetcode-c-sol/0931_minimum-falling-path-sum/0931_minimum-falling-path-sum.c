
#define MIN(a, b) (a < b ? a : b)
static inline int min3(int *n, int i1, int i2, int i3, int sz)
{
    int min = n[i1];
    if (i2 >= 0)
        min = MIN(n[i2], min);
    if (i3 < sz)
        min = MIN(n[i3], min);

    return min;
}

int minFallingPathSum(int** matrix, int matrixSize, int* matrixColSize)
{
    int ret = INT_MAX;
    for (int r = 1; r < matrixSize; r++) {
        for (int c = 0; c < matrixSize; c++) {
            matrix[r][c] = matrix[r][c] + min3(matrix[r-1], c, c-1, c+1, matrixSize);
        }
    }
    for (int c = 0; c < matrixSize; c++)
        ret = MIN(ret, matrix[matrixSize-1][c]);

    return ret;
}
