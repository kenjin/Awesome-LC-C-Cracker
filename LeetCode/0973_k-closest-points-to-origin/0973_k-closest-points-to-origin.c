
typedef struct __data {
    int idx;  /* points index */
    int dist; /* euclidean distance */
} DATA;

static inline void swap(DATA *d1, DATA *d2)
{
    DATA tmp;
    tmp.idx = d1->idx;
    tmp.dist = d1->dist;
    d1->idx = d2->idx;
    d1->dist = d2->dist;
    d2->idx = tmp.idx;
    d2->dist = tmp.dist;
}

static void spec_qsort(DATA *d, int dsize, int K)
{
    if (dsize <= 1 || K <= 0)
        return;

    /* partition */
    int pivot = d[dsize - 1].dist;
    int sidx = -1, lidx;
    for (lidx = 0; lidx < dsize - 1; lidx++) {
        if (d[lidx].dist < pivot) {
            sidx++;
            swap(&d[sidx], &d[lidx]);
        }
    }
    sidx++;
    swap(&d[sidx], &d[dsize - 1]);

    /* recursive sort for left-half and right-half */
    spec_qsort(d, sidx, K);
    if (sidx < K)
        spec_qsort(&(d[sidx + 1]), dsize - 1 - sidx, K - sidx);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **kClosest(int **points,
               int pointsSize,
               int *pointsColSize,
               int K,
               int *returnSize,
               int **returnColumnSizes)
{
    DATA *d = malloc(pointsSize * sizeof(DATA));
    for (int i = 0; i < pointsSize; i++) {
        d[i].idx = i;
        d[i].dist =
            (points[i][0]) * (points[i][0]) + (points[i][1]) * (points[i][1]);
    }

    spec_qsort(d, pointsSize, K);

    *returnSize = K;
    int **ret = malloc(sizeof(int *) * K);
    *returnColumnSizes = malloc(sizeof(int) * K);
    for (int i = 0; i < K; i++) {
        (*returnColumnSizes)[i] = 2;
        ret[i] = malloc(sizeof(int) * 2);
        int cur_idx = d[i].idx;
        ret[i][0] = points[cur_idx][0];
        ret[i][1] = points[cur_idx][1];
    }

    free(d);
    return ret;
}
