
static inline int min3(a, b, c)
{
    if (a < b)
        return (a < c ? a : c);
    else
        return (b < c ? b : c);
}

int minDistance(char *word1, char *word2)
{
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            /* If first string is empty, insert all characters of second string
             */
            if (i == 0)
                dp[i][j] = j;
            /* If second string is empty, delete all characters of first string
             */
            else if (j == 0)
                dp[i][j] = i;
            /* If last char of first string is same as last char of second
             * string */
            else if (word1[i - 1] == word2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min3(dp[i][j - 1] /* insert */,
                                    dp[i - 1][j] /* Delete */,
                                    dp[i - 1][j - 1] /* Replace */);
        }
    }

    return dp[len1][len2];
}
