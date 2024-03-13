int pivotInteger(int n)
{
    int hsum = 0, tsum = ((1 + n) * n) >> 1;
    for (int i = 1; i <= n; i++) {
        hsum += i;
        if (hsum == tsum)
            return i;
        tsum -= i;
    }
    return -1;
}
