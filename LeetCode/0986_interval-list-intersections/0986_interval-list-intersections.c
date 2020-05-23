#define MIN(a, b) (a < b ? a : b);
#define MAX(a, b) (a > b ? a : b);

static inline int **add_result(int **ret,
                               int *returnSize,
                               int **returnColumnSizes,
                               int x,
                               int y)
{
    (*returnColumnSizes)[*returnSize] = 2;
    ret[*returnSize] = malloc(sizeof(int) * 2);
    ret[*returnSize][0] = x;
    ret[*returnSize][1] = y;
    *returnSize += 1;
    return ret;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **intervalIntersection(int **A,
                           int ASize,
                           int *AColSize,
                           int **B,
                           int BSize,
                           int *BColSize,
                           int *returnSize,
                           int **returnColumnSizes)
{
    int **ret = malloc(sizeof(int *) * (ASize + BSize));
    *returnSize = 0;
    *returnColumnSizes = malloc(sizeof(int) * (ASize + BSize));

    int aidx = 0, bidx = 0;
    while (aidx < ASize && bidx < BSize) {
        int lb = MAX(A[aidx][0], B[bidx][0]);
        int ub = MIN(A[aidx][1], B[bidx][1]);
        if (lb <= ub)
            ret = add_result(ret, returnSize, returnColumnSizes, lb, ub);

        if (A[aidx][1] < B[bidx][1])
            aidx++;
        else
            bidx++;
    }

    return ret;
}
