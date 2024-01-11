#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes) 
{
    int **ret = malloc(sizeof(int *)*(intervalsSize + 1));
    *returnColumnSizes = malloc(sizeof(int)*(intervalsSize + 1));
    int ret_ctr = 0, idx = 0;

    // Handle the non-opverlap partition
    while (idx < intervalsSize && newInterval[0] > intervals[idx][1]) {
        ret[ret_ctr] = intervals[idx]; // use original ptr to ignore mem alloc
        (*returnColumnSizes)[ret_ctr] = 2;
        ret_ctr++;
        idx++;
    }

    // Use tmp to detect the overlapping, it will occur if tmp != idx
    int tmp = idx;
    while (idx < intervalsSize &&  newInterval[1] >= intervals[idx][0])
        idx++;

    if (tmp != idx) {
        // update opverlapping interval
        newInterval[0] = MIN(intervals[tmp][0], newInterval[0]);
        newInterval[1] = MAX(intervals[idx-1][1], newInterval[1]);
    }
    ret[ret_ctr] = (int *)calloc(2, sizeof(int));
    ret[ret_ctr][0] = newInterval[0];
    ret[ret_ctr][1] = newInterval[1];
    (*returnColumnSizes)[ret_ctr] = 2;
    ret_ctr++;

    // Handle the rest of non-opverlap partition
    while (idx < intervalsSize) {
        ret[ret_ctr] = intervals[idx];
        (*returnColumnSizes)[ret_ctr] = 2;
        ret_ctr++;
        idx++;
    }

    *returnSize = ret_ctr;
    return ret;
}
