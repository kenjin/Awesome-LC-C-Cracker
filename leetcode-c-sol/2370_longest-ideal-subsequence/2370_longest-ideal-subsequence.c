
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int longestIdealString(char *s, int k)
{
    int slen = strlen(s);
    int *dp = (int *)malloc(slen * sizeof(int));
    int last_occur[26] = {0}, longest_len = 1;

    for (int i = 0; i < slen; ++i)
        dp[i] = 1;

    memset(last_occur, -1, 26 * sizeof(int));
    last_occur[s[0] - 'a'] = 0;

    for (int i = 1; i < slen; ++i) {
        // Try extending the ideal string including all characters within 'k' distance of current character
        for (int ch_idx = 0; ch_idx < 26; ch_idx++) {
            int diff = abs(s[i] - 'a' - ch_idx);
            if (diff > k)
                continue;
            // Check if we have seen other character before and extend the ideal string length
            if (last_occur[ch_idx] != -1)
                dp[i] = MAX(dp[i], dp[last_occur[ch_idx]] + 1);
        }
        // Update the last occurrence index for the current character, also longest length found so far
        last_occur[s[i] - 'a'] = i;
        longest_len = MAX(longest_len, dp[i]);
    }

    free(dp);
    return longest_len;
}

