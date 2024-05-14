
#define VISITED_BIT (0x80)
#define GET_GOLD(v) (v & ~VISITED_BIT)
#define IS_VISITED(v) (v & VISITED_BIT)
#define SET_VISITED(v) (v |= VISITED_BIT)
#define UNSET_VISITED(v) (v &= ~VISITED_BIT)

static void path_gold_dfs(int** grid, int row_sz, int col_sz, int cur_x,
                          int cur_y, int sum, int* ret)
{
    if (cur_x < 0 || cur_x == row_sz || cur_y < 0 || cur_y == col_sz ||
        grid[cur_x][cur_y] == 0 || IS_VISITED(grid[cur_x][cur_y])) {
        *ret = (*ret > sum ? *ret : sum);
        return;
    }

    SET_VISITED(grid[cur_x][cur_y]);
    sum += GET_GOLD(grid[cur_x][cur_y]);
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (int x = 0; x < 4; x++)
        path_gold_dfs(grid, row_sz, col_sz, cur_x + dir[x][0],
                      cur_y + dir[x][1], sum, ret);

    UNSET_VISITED(grid[cur_x][cur_y]);
}

int getMaximumGold(int** grid, int gridSize, int* gridColSize)
{
    int ret = 0, sum = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++)
            path_gold_dfs(grid, gridSize, gridColSize[0], i, j, sum, &ret);
    }
    return ret;
}
