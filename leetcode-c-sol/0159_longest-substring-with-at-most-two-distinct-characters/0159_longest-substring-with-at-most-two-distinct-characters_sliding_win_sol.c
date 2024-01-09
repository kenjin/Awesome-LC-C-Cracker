#define MAX(a, b) (a > b ? a : b)

int lengthOfLongestSubstringTwoDistinct(char* s)
{
    int set[128] = {0}, slen = strlen(s);
    int head = 0, tail = 0, ret = 0, distinct = 2;
    while (tail < slen) {
        set[s[tail]]++;
        // process distinct case
        if (set[s[tail]] == 1) {
            distinct--;
            while (distinct < 0) {
                set[s[head]]--;
                if (!set[s[head]])
                    distinct++;

                head++;
            }
        }

        int win_sz = (tail - head + 1);
        ret = MAX(ret, win_sz);
        tail++;
    }

    return ret;
}
