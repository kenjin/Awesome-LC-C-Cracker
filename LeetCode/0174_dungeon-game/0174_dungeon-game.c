#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

int calculateMinimumHP(int **dungeon, int dungeonSize, int *dungeonColSize)
{
    int r_sz = dungeonSize, c_sz = dungeonColSize[0];
    int *dp = malloc(sizeof(int) * (c_sz + 1));
    for (int i = 0; i <= c_sz; i++)
        dp[i] = INT_MAX;

    dp[c_sz - 1] = 1;

    for (int i = r_sz - 1; i >= 0; i--) {
        for (int j = c_sz - 1; j >= 0; j--) {
            dp[j] = MAX(1, MIN(dp[j], dp[j + 1]) - dungeon[i][j]);
        }
    }

    int ret = dp[0];
    free(dp);

    return ret;
}
