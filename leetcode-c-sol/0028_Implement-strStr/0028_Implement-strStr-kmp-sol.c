
static void create_lps_arr(int *lps, char *pattern, int len)
{
    lps[0] = 0;
    int prev = 0, idx = 1;
    while (idx < len) {
        if (pattern[idx] == pattern[prev]) {
            lps[idx] = prev + 1;
            prev++;
            idx++;
        } else {
            if (prev == 0) {
                // pattern[i] != pattern[prev] && prev == 0
                lps[idx] = 0;
                idx++;
            } else {
                // pattern[i] != pattern[prev] && prev != 0
                prev = lps[prev-1];
            }
        }
    }

}

int strStr(char* haystack, char* needle)
{
    int nlen = strlen(needle);
    int *lps = malloc(sizeof(int)*nlen);
    create_lps_arr(lps, needle, nlen);

    int h_idx = 0, n_idx = 0, ret = -1;
    while (h_idx < strlen(haystack)) {
        if (haystack[h_idx] == needle[n_idx]) {
            h_idx++;
            n_idx++;
        } else {
            if (n_idx == 0) {
                h_idx++;
            } else {
                n_idx = lps[n_idx - 1];
            }
        }
        // Finish all the needle char
        if (n_idx == nlen) {
            ret = h_idx - nlen;
            break;
        }
    }

    free(lps);
    return ret;
}

