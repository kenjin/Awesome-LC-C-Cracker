
static int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

int hIndex(int *citations, int citationsSize)
{
    qsort(citations, citationsSize, sizeof(int), compare);

    int left = 0, right = citationsSize - 1;
    while (left <= right) {
        int mid = ((left - right) >> 1) + right;
        if (citations[mid] == citationsSize - mid)
            return citationsSize - mid;
        else if (citations[mid] < citationsSize - mid)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return citationsSize - left;
}
