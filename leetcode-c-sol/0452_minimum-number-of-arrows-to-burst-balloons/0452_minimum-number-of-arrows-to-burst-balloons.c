
static int compare(const void *a, const void *b)
{
    int _a = ((*(int**)a)[1]);
    int _b = ((*(int**)b)[1]);

    return (_a < _b)? -1: (_a > _b);   
}


int findMinArrowShots(int** points, int pointsSize, int* pointsColSize)
{
    qsort(points, pointsSize, sizeof(int *), compare);
    int ret = 1, prev_tail = points[0][1];
    for (int i = 1; i < pointsSize; i++) {
        if (points[i][0] > prev_tail) {
            prev_tail = points[i][1];
            ret++;
        }
    }

    return ret;
}
