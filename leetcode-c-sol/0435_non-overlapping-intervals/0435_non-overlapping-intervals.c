
static int compare(const void *a, const void *b)
{
    int *n1 = *(int **) a;
    int *n2 = *(int **) b;
    return ((n1[0] == n2[0]) ? (n1[1] - n2[1]) : (n1[0] - n2[0]));
}

int eraseOverlapIntervals(int **intervals,
                          int intervals_sz,
                          int *intervals_col_sz)
{
    qsort(intervals, intervals_sz, sizeof(int *), compare);

    int ret = 0, cur_idx = 0;
    for (int i = 1; i < intervals_sz; i++) {
        if (intervals[i][0] < intervals[cur_idx][1]) {
            ret++;
            cur_idx = (intervals[i][1] < intervals[cur_idx][1] ? i : cur_idx);
        } else {
            cur_idx = i;
        }
    }

    return ret;
}
