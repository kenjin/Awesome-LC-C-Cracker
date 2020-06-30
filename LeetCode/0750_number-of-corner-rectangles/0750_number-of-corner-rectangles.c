

int countCornerRectangles(int **grid, int gridSize, int *gridColSize)
{
    int ret = 0;
    int col_sz = gridColSize[0];
    for (int i = 0; i < gridSize; i++) {
        for (int j = i + 1; j < gridSize; j++) {
            int line_ctr = 0;
            for (int x = 0; x < col_sz; x++) {
                if (grid[i][x] && grid[j][x])
                    line_ctr++;
            }
            ret += ((line_ctr * (line_ctr - 1)) >> 1);
        }
    }

    return ret;
}