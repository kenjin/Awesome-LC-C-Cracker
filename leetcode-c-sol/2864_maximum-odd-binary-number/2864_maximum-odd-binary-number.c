char* maximumOddBinaryNumber(char* s)
{
    int ctr = 0, idx = 0;
    while (s[idx]) {
        if (s[idx] == '1')
            ctr++;
        s[idx++] = '0';
    }

    s[idx - 1] = '1';
    int head = 0;
    while (ctr > 1) {
        s[head++] = '1';
        ctr--;
    }

    return s;
}
