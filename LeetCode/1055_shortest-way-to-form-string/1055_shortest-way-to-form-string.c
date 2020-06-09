
int shortestWay(char *source, char *target)
{
    char alpha[26] = {0};
    int slen = strlen(source);
    int tlen = strlen(target);

    for (int x = 0; x < slen; x++)
        alpha[source[x] - 'a'] = 1;

    int sc_idx = 0, res = 1;
    for (int ta_idx = 0; ta_idx < tlen; ta_idx++, sc_idx++) {
        if (!alpha[target[ta_idx] - 'a'])
            return -1;

        while (sc_idx < slen && source[sc_idx] != target[ta_idx])
            sc_idx++;

        if (sc_idx == slen) {
            res++;
            ta_idx--;
            sc_idx = -1;
        }
    }

    return res;
}
