#define MAX(a, b) (a > b ? a : b)

int characterReplacement(char* s, int k)
{
    int slen = strlen(s);
    int set[26] = {0};
    int ret = 0, tmp_max = 0, head = 0, total = 0;
    for (int tail = 0; tail < slen; tail++) {
        set[s[tail]-'A']++;
        tmp_max = MAX(tmp_max, set[s[tail]-'A']);
        total++;
        if (total - tmp_max <= k) {
            ret = MAX(ret, tail - head + 1);
        } else {
            set[s[head]-'A']--;
            head++;
            total--;
        }
    }
    return ret;
}
