/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * struct BinaryMatrix {
 *     int (*get)(struct BinaryMatrix*, int, int);
 *     int* (*dimensions)(struct BinaryMatrix*);
 * };
 */

int leftMostColumnWithOne(struct BinaryMatrix *matrix)
{
    int *d = matrix->dimensions(matrix);
    int row_sz = d[0];
    int col_sz = d[1];

    int cur_r = 0, cur_c = col_sz - 1;
    int ret = -1;
    while (cur_r < row_sz && cur_c >= 0) {
        if (0 == matrix->get(matrix, cur_r, cur_c))
            cur_r++;
        else
            ret = cur_c--;
    }

    return ret;
}
