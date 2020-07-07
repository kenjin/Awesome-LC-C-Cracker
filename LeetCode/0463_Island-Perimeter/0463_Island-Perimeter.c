
int islandPerimeter(int **grid, int gridSize, int *gridColSize)
{
    int ret = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < *gridColSize; j++) {
            if (grid[i][j]) {
                ret += 4;
                if (i > 0 && grid[i - 1][j])
                    ret -= 2;
                if (j > 0 && grid[i][j - 1])
                    ret -= 2;
            }
        }
    }

    return ret;
}