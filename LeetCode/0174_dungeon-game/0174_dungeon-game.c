#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

int calculateMinimumHP(int **dungeon, int dungeonSize, int *dungeonColSize)
{
    int r_sz = dungeonSize, c_sz = dungeonColSize[0];
    int **dp = malloc(sizeof(int *) * (r_sz + 1));
    for (int i = 0; i <= r_sz; i++) {
        dp[i] = malloc(sizeof(int) * (c_sz + 1));
        dp[i][c_sz] = INT_MAX;
    }
    for (int i = 0; i <= c_sz; i++)
        dp[r_sz][i] = INT_MAX;

    dp[r_sz][c_sz - 1] = 1;
    dp[r_sz - 1][c_sz] = 1;

    for (int i = r_sz - 1; i >= 0; i--) {
        for (int j = c_sz - 1; j >= 0; j--) {
            dp[i][j] = MAX(1, MIN(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j]);
        }
    }

    int ret = dp[0][0];
    for (int i = 0; i < r_sz; i++)
        free(dp[i]);
    free(dp);

    return ret;
}
