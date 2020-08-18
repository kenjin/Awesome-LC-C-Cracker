typedef struct __data {
    int idx;
    int match;
    int len;
} DATA;

char *shortestCompletingWord(char *licensePlate, char **words, int words_sz)
{
    int set[26] = {0};
    char *cur = licensePlate;
    while (*cur) {
        if (*cur >= 'A' && *cur <= 'Z') {
            set[*cur - 'A'] += 1;
        } else if (*cur >= 'a' && *cur <= 'z') {
            set[*cur - 'a'] += 1;
        }
        cur++;
    }

    DATA ret;
    ret.match = 0;
    ret.len = 0;
    for (int i = 0; i < words_sz; i++) {
        int tmp[26] = {0}, match = 0, cur_len = 0;
        memcpy(tmp, set, sizeof(int) * 26);
        cur = words[i];
        while (*cur) {
            int idx = -1;
            if (*cur >= 'A' && *cur <= 'Z') {
                idx = *cur - 'A';
            } else if (*cur >= 'a' && *cur <= 'z') {
                idx = *cur - 'a';
            }

            if (idx != -1 && tmp[idx] > 0) {
                tmp[idx] -= 1;
                match++;
            }
            cur++;
            cur_len++;
        }

        if ((match > ret.match) || (match == ret.match && ret.len > cur_len)) {
            ret.idx = i;
            ret.match = match;
            ret.len = cur_len;
        }
    }

    return words[ret.idx];
}
