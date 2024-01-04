int firstBadVersion(int n)
{
    int head = 1, tail = n;
    while (head <= tail) {
        int mid = tail + ((head - tail) >> 1);

        if (isBadVersion(mid)) {
            tail = mid - 1;
        } else {
            if ((mid + 1 <= n) && isBadVersion(mid + 1))
                return mid + 1;
            head = mid + 1;
        }
    }

    return 1;
}
