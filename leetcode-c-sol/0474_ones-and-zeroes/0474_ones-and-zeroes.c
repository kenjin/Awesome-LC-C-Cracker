#define MAX(a, b) (a > b ? a : b)
int findMaxForm(char** strs, int strsSize, int m, int n)
{
    // dp[i][j]: represents the maximum number of strings that can be formed with i zeros and j ones.
    // dp[i][j] = max(dp[i][j], dp[i-zeros][j-ones] + 1);
    int **dp = malloc(sizeof(int*)*(m + 1));
    for (int i = 0; i <= m; i++)
        dp[i] = calloc(n + 1, sizeof(int));

    for (int i = 0; i < strsSize; i++) {
        char *tmp = strs[i];
        int num0 = 0, num1 = 0;
        while (*tmp) {
            if (*tmp == '0')
                num0++;
            else 
                num1++;
            tmp++;
        }

        for (int x = m; x >= num0; x--) {
            for (int y = n; y >= num1; y--) {
                dp[x][y] = MAX(dp[x-num0][y-num1] + 1, dp[x][y]);
            }
        }
    }

    int ret = dp[m][n];
    for (int i = 0; i <= m; i++)   
        free(dp[i]);
    free(dp);

    return ret;
}
