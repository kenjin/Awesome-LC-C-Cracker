static bool find_break(char **dp, int baseIdx, int size)
{
    if (baseIdx >= size)
        return true;

    for (int i = 0; i < size; i++) {
        if (dp[baseIdx][i] && find_break(dp, i + 1, size))
            return true;
        else /* because find_break(dp, i + 1, size) was failed from above codes
                */
            dp[baseIdx][i] = 0;
    }
    return false;
}

bool wordBreak(char *s, char **wordDict, int wordDictSize)
{
    int len = strlen(s);
    /* dp[i][j] - indicate that string index i to j can become a word break or
     * not */
    char **dp = calloc(len, sizeof(char *));
    for (int i = 0; i < len; i++)
        dp[i] = calloc(len, sizeof(char));

    for (int i = 0; i < wordDictSize; i++) {
        char *tmp = strstr(s, wordDict[i]);
        int wd_len = strlen(wordDict[i]);
        while (tmp != NULL) {
            int start = tmp - s;
            int end = start + wd_len - 1;
            dp[start][end] = 1;
            /* continue to find from the next char */
            tmp = strstr(&(s[start + 1]), wordDict[i]);
        }
    }

    bool ret = find_break(dp, 0, len);
    for (int i = 0; i < len; i++)
        free(dp[i]);
    free(dp);
    return ret;
}
