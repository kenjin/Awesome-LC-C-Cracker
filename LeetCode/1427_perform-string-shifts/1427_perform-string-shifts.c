char *stringShift(char *s, int **shift, int shift_sz, int *shift_col_sz)
{
    int len = strlen(s);
    int move = 0;
    for (int i = 0; i < shift_sz; i++) {
        int tmp = shift[i][1] % len;
        if (!shift[i][0])
            tmp = len - shift[i][1];
        move = (move + tmp + len) % len;
    }

    char *dup = malloc(sizeof(char) * len);
    memcpy(dup, s, sizeof(char) * len);
    memcpy(&s[move], dup, sizeof(char) * (len - move));
    memcpy(s, &dup[len - move], sizeof(char) * (move));
    free(dup);
    return s;
}
