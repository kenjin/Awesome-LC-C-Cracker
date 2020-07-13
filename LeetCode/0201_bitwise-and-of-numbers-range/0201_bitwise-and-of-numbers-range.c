
int rangeBitwiseAnd(int m, int n)
{
    int base = 0, ret = INT_MAX;
    while ((m & ret) != (n & ret)) {
        int cur = (0x1 << (base++));
        ret &= ~cur;
    }
    return m & ret;
}
