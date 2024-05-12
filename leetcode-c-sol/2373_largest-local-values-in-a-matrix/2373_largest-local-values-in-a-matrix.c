#define MAX(a, b) (a > b ? a : b)

int** largestLocal(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes)
{
    int **ret = malloc(sizeof(int *)*(gridSize - 2));
    *returnColumnSizes = malloc(sizeof(int)*(gridSize - 2));
    *returnSize = gridSize - 2;
    for (int i = 0; i < gridSize - 2; i++) {
        ret[i] = malloc(sizeof(int)*(gridSize - 2));
        (*returnColumnSizes)[i] = gridSize - 2;
    } 

    for (int x = 0; x < gridSize - 2; x++) {
        for (int y = 0; y < gridSize - 2; y++) {
            int max_tmp = ret[x][y];
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++)
                    max_tmp = MAX(max_tmp, grid[x + i][y + j]);
            }
            ret[x][y] = max_tmp;
        }
    }
    return ret;
}
