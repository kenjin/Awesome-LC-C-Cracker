
char *convert(char *s, int numRows)
{
    if (numRows == 1)
        return s;

    int base = (numRows << 1) - 2;
    int slen = strlen(s);
    int ret_cnt = 0;
    char *ret = calloc(slen + 1, sizeof(char));
    for (int i = 0; i < numRows; i++) {
        int idx = i;
        int idx_slash = base - i;
        while (idx < slen) {
            ret[ret_cnt++] = s[idx];
            idx += base;
            if (i > 0 && i < (numRows - 1) && idx_slash < slen) {
                ret[ret_cnt++] = s[idx_slash];
                idx_slash += base;
            }
        }
    }

    return ret;
}
