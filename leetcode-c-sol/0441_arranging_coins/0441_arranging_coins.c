
int arrangeCoins(int n)
{
#if 1
    if (n <= 1)
        return n;
    long min = 1, max = n;
    while (min < max) {
        long mid = min + ((max - min) >> 1);
        if (((mid * (mid + 1)) >> 1) <= n)
            min = mid + 1;
        else
            max = mid;
    }

    return min - 1;
#else
    return (int) ((-1 + sqrt(1 + 8 * (long) n)) / 2);
#endif
}