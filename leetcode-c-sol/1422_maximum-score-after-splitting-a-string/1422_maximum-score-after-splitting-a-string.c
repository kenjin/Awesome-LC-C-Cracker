

int maxScore(char *s)
{
    int len = strlen(s);
    int *r1 = malloc(sizeof(int) * len);
    int *l0 = malloc(sizeof(int) * len);

    l0[0] = (*s == '0' ? 1 : 0);
    r1[0] = (s[len - 1] == '1' ? 1 : 0);
    for (int i = 1; i < len; i++) {
        r1[i] = r1[i - 1];
        l0[i] = l0[i - 1];
        if (s[i] == '0')
            l0[i] += 1;
        if (s[len - i - 1] == '1')
            r1[i] += 1;
    }

    int max = 0;
    for (int i = 0; i < len - 1; i++) {
        int tmp = l0[i] + r1[len - i - 2];
        max = (max > tmp ? max : tmp);
    }

    free(l0);
    free(r1);
    return max;
}