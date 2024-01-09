#define MAX(a, b) (a > b ? a : b)

int lengthOfLongestSubstringTwoDistinct(char* s) {
    int slen = strlen(s);
    char prev = s[0];
    char set[2] = {prev, 0};

    int ret= 0, tmp_ret = 1, cur_repeat = 1, toggle = 0;
    for (int i = 1; i < slen; i++) {
        if (s[i] != prev) {
            toggle ^= 1;
            if (set[toggle] != 0 && set[toggle] != s[i]) {
                // Find third distinct char, update the temp result.
                ret = MAX(ret, tmp_ret);
                tmp_ret = cur_repeat + 1;
            } else {
                // Fin second distinct char, keep counting temp max.
                tmp_ret++;
            }
            // Update the disctinct char and reset it's repeat ctr.
            set[toggle] = s[i];
            cur_repeat = 1;
        } else {
            cur_repeat++;
            tmp_ret++;
        }
        prev = s[i];
    }
    return MAX(ret, tmp_ret);
}
