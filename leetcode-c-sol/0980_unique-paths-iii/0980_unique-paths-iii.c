static void dfs(int** grid, int row_sz, int col_sz, int cur_x, int cur_y, int steps, int *ret)
{
    if (cur_x < 0 || cur_x == row_sz || cur_y < 0 || cur_y == col_sz || 
            grid[cur_x][cur_y] == -1 || grid[cur_x][cur_y] == -2) {
        return;
    }
    if (steps == 0 || grid[cur_x][cur_y] == 2) {
        if (steps == 0  && grid[cur_x][cur_y] == 2)
            *ret += 1;
        return ;
    }

    grid[cur_x][cur_y] = -2; // Set -2 to indicate this node is visited
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (int i = 0; i < 4; i++) {
        dfs(grid, row_sz, col_sz, cur_x + dir[i][0], cur_y + dir[i][1], steps - 1, ret);
    }
    grid[cur_x][cur_y] = 0;
}

int uniquePathsIII(int** grid, int gridSize, int* gridColSize)
{
    int start[2], steps = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == 1) {
                start[0] = i;
                start[1] = j;
            } else if (grid[i][j] == 2 || grid[i][j] == 0) {
                steps++;
            }
        }
    }

    int ret = 0;
    dfs(grid, gridSize, gridColSize[0], start[0], start[1], steps, &ret);
    return ret;
}
