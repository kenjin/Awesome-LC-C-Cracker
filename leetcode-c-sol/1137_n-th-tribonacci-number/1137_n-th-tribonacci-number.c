
int tribonacci(int n)
{
    if (n < 3)
        return (n == 0 ? 0 : 1);

    int n0 = 0, n1 = 1, n2 = 1;
    for (int i = 3; i <= n; i++) {
        int tmp = n0 + n1 + n2;
        n0 = n1;
        n1 = n2;
        n2 = tmp;
    }

    return n2;
}
