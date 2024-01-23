/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generateMatrix(int n, int* returnSize, int** returnColumnSizes)
{
    int **ret = malloc(sizeof(int *) * n);
    *returnColumnSizes = malloc(sizeof(int) * n);
    *returnSize = n;
    for (int i = 0; i < n; i++) {
        ret[i] = malloc(sizeof(int) * n);
        (*returnColumnSizes)[i] = n;
    }

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // right, down, left, up
    int didx = 0, row_tail = n, col_tail = n, row_head = 1, col_head = 0;
    int x = 0, y = 0;
    for (int ctr = 1; ctr <= n*n; ctr++) {
        ret[x][y] = ctr;
        if (didx == 0 && y + 1 == col_tail) {
            didx = 1;
            col_tail--;
        } else if (didx == 1 && x + 1 == row_tail) {
            didx = 2;
            row_tail--;
        } else if (didx == 2 && y == col_head) {
            didx = 3;
            col_head++;
        } else if (didx == 3 && x == row_head) {
            didx = 0;
            row_head++;
        }
        x += dir[didx][0];
        y += dir[didx][1];
    }
    return ret;
}
