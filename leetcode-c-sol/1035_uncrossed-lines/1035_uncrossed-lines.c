
static inline int max3(int a, int b, int c)
{
    if (a < b)
        return (b > c ? b : c);
    else
        return (a > c ? a : c);
}

int maxUncrossedLines(int *A, int ASize, int *B, int BSize)
{
    int **dp = malloc(sizeof(int *) * ASize);
    dp[0] = calloc(BSize, sizeof(int));
    dp[0][0] = (A[0] == B[0] ? 1 : 0);
    for (int i = 1; i < ASize; i++) {
        dp[i] = calloc(BSize, sizeof(int));
        dp[i][0] = (A[i] == B[0] ? 1 : dp[i - 1][0]);
    }


    for (int i = 1; i < BSize; i++)
        dp[0][i] = (A[0] == B[i] ? 1 : dp[0][i - 1]);

    for (int x = 1; x < ASize; x++) {
        for (int y = 1; y < BSize; y++) {
            if (A[x] == B[y])
                dp[x][y] = dp[x - 1][y - 1] + 1;
            else
                dp[x][y] = max3(dp[x][y - 1], dp[x - 1][y], dp[x - 1][y - 1]);
        }
    }


    int ret = dp[ASize - 1][BSize - 1];
    for (int i = 0; i < ASize; i++)
        free(dp[i]);
    free(dp);
    return ret;
}
