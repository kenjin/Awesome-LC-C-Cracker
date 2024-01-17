/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#define MAX(a, b) (a > b ? a : b)

int compare(const void *a, const void *b)
{
    const int *n1 = *(int **)a;
    const int *n2 = *(int **)b;
    return (n1[0] < n2[0])? -1: (n1[0] > n2[0]);
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes)
{
    qsort(intervals, intervalsSize, sizeof(int *), compare);

    *returnColumnSizes = malloc(sizeof(int)*intervalsSize);
    int **ret = malloc(sizeof(int *)*intervalsSize);
    ret[0] = malloc(sizeof(int)*2);
    ret[0][0] = intervals[0][0];
    ret[0][1] = intervals[0][1];
    (*returnColumnSizes)[0] = 2;

    int ret_cnt = 1;
    int prev = intervals[0][1];
    for (int i = 1; i < intervalsSize; i++) {
        if (prev >= intervals[i][0]) {
            ret[ret_cnt - 1][1] = MAX(prev, intervals[i][1]);
        } else {
            ret[ret_cnt] = malloc(sizeof(int)*2);
            ret[ret_cnt][0] = intervals[i][0];
            ret[ret_cnt][1] = intervals[i][1];
            (*returnColumnSizes)[ret_cnt] = 2;
            ret_cnt++;
        }
        prev = MAX(prev, intervals[i][1]);
    }
    *returnSize = ret_cnt;
    return ret;
}

int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes) {
    intervals = realloc(intervals, sizeof(int*)*(intervalsSize + 1));
    intervals[intervalsSize] = malloc(sizeof(int)*2);
    intervals[intervalsSize][0] = newInterval[0];
    intervals[intervalsSize][1] = newInterval[1];
    intervalsSize++;
    return merge(intervals, intervalsSize, intervalsColSize, returnSize, returnColumnSizes);
}
