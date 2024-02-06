
static void dfs(int** grid, int cur_x, int cur_y, int row_sz, int col_sz) {
    if (cur_x < 0 || cur_y < 0 || cur_x == row_sz || cur_y == col_sz ||
        !grid[cur_x][cur_y])
        return;

    grid[cur_x][cur_y] = 0;
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (int i = 0; i < 4; i++)
        dfs(grid, cur_x + dir[i][0], cur_y + dir[i][1], row_sz, col_sz);
}

int numEnclaves(int** grid, int gridSize, int* gridColSize) {
    for (int i = 0; i < gridSize; i++) {
        dfs(grid, i, 0, gridSize, gridColSize[0]);
        dfs(grid, i, gridColSize[0] - 1, gridSize, gridColSize[0]);
    }
    for (int j = 1; j < gridColSize[0] - 1; j++) {
        dfs(grid, 0, j, gridSize, gridColSize[0]);
        dfs(grid, gridSize - 1, j, gridSize, gridColSize[0]);
    }

    int ret = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            if (grid[i][j])
                ret++;
        }
    }

    return ret;
}
