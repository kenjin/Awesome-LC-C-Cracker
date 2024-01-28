int numSubmatrixSumTarget(int** matrix, int matrixSize, int* matrixColSize, int target)
{
    int ret = 0, col_sz = matrixColSize[0];
    // prefix-sum to recude duplicate of sum calculation
    int **prefix_sum = malloc(sizeof(int*) * (matrixSize+1));
    for (int i = 0; i <= matrixSize; i++)
        prefix_sum[i] = calloc(col_sz+1, sizeof(int));

    for (int i = 1; i <= matrixSize; i++) {
        for (int j = 1; j <= col_sz; j++) {
            prefix_sum[i][j] = prefix_sum[i-1][j] + prefix_sum[i][j-1] - prefix_sum[i-1][j-1] + matrix[i-1][j-1];
            //   printf("prefix[%d, %d] = %d\n", i, j, prefix_sum[i][j]);
        }
    }

    for (int i = 1; i <= matrixSize; i++) {
        for (int j = 1; j <= col_sz; j++) {
            // Check all sub-matrix
            for (int x = 1; x <= i; x++) {
                for (int y = 1; y <= j; y++) {
                    if (target == (prefix_sum[i][j] - prefix_sum[i][y - 1] - prefix_sum[x - 1][j] + prefix_sum[x - 1][y - 1]))
                        ret++;
                }
            }
        }
    }

    return ret;
}
