
int hIndex(int *citations, int citationsSize)
{
    int left = 0, right = citationsSize - 1;
    while (left <= right) {
        int mid = ((right - left) >> 1) + left;
        if (citations[mid] == citationsSize - mid)
            return citationsSize - mid;
        else if (citations[mid] > citationsSize - mid)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return citationsSize - left;
}
