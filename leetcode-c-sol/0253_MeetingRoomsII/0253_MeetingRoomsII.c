
int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

int minMeetingRooms(int **intervals, int intervalsSize, int *intervalsColSize)
{
    int *start = malloc(sizeof(int) * intervalsSize);
    int *end = malloc(sizeof(int) * intervalsSize);
    for (int i = 0; i < intervalsSize; i++) {
        start[i] = intervals[i][0];
        end[i] = intervals[i][1];
    }

    qsort(start, intervalsSize, sizeof(int), compare);
    qsort(end, intervalsSize, sizeof(int), compare);

    int ret = 0, end_idx = 0;
    for (int i = 0; i < intervalsSize; i++) {
        if (start[i] < end[end_idx])
            ret++;
        else
            end_idx++;
    }

    free(start);
    free(end);
    return ret;
}
