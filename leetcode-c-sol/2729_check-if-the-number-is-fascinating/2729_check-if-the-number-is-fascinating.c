bool isFascinating(int n)
{
    int n1 = n, n2 = (n << 1), n3 = (n2 + n1);
    if (n3 > 1000)
        return false;

    unsigned short hash = 0x0;
    while (n3 > 0) {
        int idx1 = n1 % 10;
        int idx2 = n2 % 10;
        int idx3 = n3 % 10;

        hash = hash | (0x1 << idx1) | (0x1 << idx2) | (0x1 << idx3);

        n1 /= 10;
        n2 /= 10;
        n3 /= 10;
    }

    return (hash == 0x03FE ? true : false);
}
