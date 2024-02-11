
#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)
int cherryPickup(int** grid, int gridSize, int* gridColSize)
{
    // constraints: 2 <= rows, cols <= 70
    int dir[3]= {-1, 0, 1};
    int col_sz = gridColSize[0];
    int ***dp = malloc(sizeof(int**)*gridSize);
    for (int i = 0; i < gridSize; i++) {
        dp[i] = malloc(sizeof(int*)*col_sz);
        for (int j = 0; j < col_sz; j++) {
            dp[i][j] = malloc(sizeof(int)*col_sz);
            for (int k = 0; k < col_sz; k++)
                dp[i][j][k] = -1;
        }
    }

    dp[0][0][col_sz - 1] = grid[0][0]+grid[0][col_sz - 1];
    for (int i = 1; i < gridSize; i++) {
        for (int bot1_idx = 0; bot1_idx < col_sz; bot1_idx++) {
            for (int bot2_idx = 0; bot2_idx < col_sz; bot2_idx++) {
                int prev = dp[i - 1][bot1_idx][bot2_idx];
                if (prev >= 0) {
                    for(int d1 = 0; d1 < 3; d1++) {
                        int c1 = bot1_idx + dir[d1];
                        for (int d2 = 0; d2 < 3; d2++) {
                            int c2 = bot2_idx + dir[d2];
                            if(c1 >= 0 && c1 < col_sz && c2 >= 0 && c2 < col_sz) {
                                if (c1 == c2) 
                                    dp[i][c1][c2] = MAX(dp[i][c1][c2], prev + grid[i][c1]);
                                else 
                                    dp[i][c1][c2] = MAX(dp[i][c1][c2], prev + grid[i][c1] + grid[i][c2]);
                            }
                        }
                    }
                }
            }
        }
    }

    int ret = 0;
    for (int i = 0; i < col_sz; i++) {
        for (int j = i + 1; j < col_sz; j++) {
            ret = MAX(ret, dp[gridSize-1][i][j]);
        }
    }

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < col_sz; j++)
            free(dp[i][j]);
        free(dp[i]);
    }
    free(dp);

    return ret;
}
