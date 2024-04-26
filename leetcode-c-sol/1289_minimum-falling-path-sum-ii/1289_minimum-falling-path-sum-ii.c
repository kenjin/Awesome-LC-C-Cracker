
static void find_small2(int *arr, int sz, int *s1, int *s2)
{
    int s_idx1 = 0;
    // Find 1st small element idx
    for (int i = 0; i < sz; i++) {
        if (arr[i] < arr[s_idx1])
            s_idx1 = i;
    }
    // Find 2nd small element idx, note that we allow duplicate element in an array.
    int s_idx2 = (s_idx1 == 0 ? 1 : 0);
    for (int i = 0; i < sz; i++) {
        if (arr[i] == arr[s_idx1] && i != s_idx1) {
            s_idx2 = i;
            break;
        }
        if (arr[i] > arr[s_idx1] && arr[i] < arr[s_idx2])
            s_idx2 = i;      
    }
    *s1 = s_idx1;
    *s2 = s_idx2;
}

int minFallingPathSum(int** grid, int gridSize, int* gridColSize)
{
    // Note that it is a n x n integer matrix grid, gridSize is same as gridColSize[0].
    if (gridSize == 1)
        return grid[0][0];

    int sidx1 = 0, sidx2 = 0;
    find_small2(grid[gridSize - 1], gridSize, &sidx1, &sidx2);

    for (int i = gridSize - 2; i >= 0; i--) {
        for (int j = 0; j < gridSize; j++)
            grid[i][j] += (j != sidx1 ? grid[i + 1][sidx1] : grid[i + 1][sidx2]);

        find_small2(grid[i], gridSize, &sidx1, &sidx2);
    }
    return grid[0][sidx1];
}
