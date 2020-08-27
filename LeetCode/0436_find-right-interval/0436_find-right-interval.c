
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct {
    int idx;
    int start;
    int end;
} data_t;

static int compare(const void *a, const void *b)
{
    return (*(data_t *) a).start - (*(data_t *) b).start;
}
// find target <= ??
static int binary_search(int target, data_t *d, int size)
{
    int head = 0, tail = size, ret = -1;
    while (head < tail) {
        int mid = head + ((tail - head) >> 1);
        if (target > d[mid].start)
            head = mid + 1;
        else
            ret = tail = mid;
    }
    return ret;
}

int *findRightInterval(int **intervals,
                       int intervals_sz,
                       int *intervals_col_sz,
                       int *return_sz)
{
    /* prepare data to record the interval and corresponding index */
    data_t *d = malloc(sizeof(data_t) * intervals_sz);
    int *ret = malloc(sizeof(int) * intervals_sz);
    for (int i = 0; i < intervals_sz; i++) {
        d[i].idx = i;
        d[i].start = intervals[i][0];
        d[i].end = intervals[i][1];
    }
    /* sort d based on start point (increase progressively) */
    qsort(d, intervals_sz, sizeof(data_t), compare);

    for (int i = 0; i < intervals_sz; i++) {
        int cur = binary_search(intervals[i][1], d, intervals_sz);
        ret[i] = (cur == -1 ? -1 : d[cur].idx);
    }

    free(d);
    *return_sz = intervals_sz;
    return ret;
}
