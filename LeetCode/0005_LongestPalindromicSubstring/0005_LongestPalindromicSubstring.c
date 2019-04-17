/**
5. Longest Palindromic Substring [Medium]

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.

Example 2:

Input: "cbbd"
Output: "bb"

*/

char* longestPalindrome(char* s) {
    int len = strlen(s);

    if (len == 0)
    {
        return "";
    } else if (len == 1)
    {
        return s;
    } else
    {
        /* DP:
           dp[i][j] means whether s[i]-s[j] is a palindromic string or not, if i > j
           dp[i][j] = dp[i+1][j-1], if i < j
           dp[i][j] = T, if i >= j

           DP example for "babad":
              b a b a d
           b  T F T F F
           a  T T F T F
           b  T T T F F
           a  T T T T F
           d  T T T T T
        */

        /* DP init */
        bool dp[len][len];
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                if (i >= j)
                {
                    dp[i][j] = true;
                } else
                {
                    dp[i][j] = false;
                }
            }
        }
		/* DP Process */
        int maxLen = 1, start = 0;
        for (int curPalindromicStrMax = 2; curPalindromicStrMax <= len; curPalindromicStrMax++)
        {
            for (int i = 0; (i + curPalindromicStrMax -1) < len; i++)
            {
                int j = i + curPalindromicStrMax - 1;
                if (s[i] != s[j])
                {
                    dp[i][j] = false;
                } else
                {
                    dp[i][j] = dp[i+1][j-1];
                    if (dp[i][j]  && maxLen < curPalindromicStrMax)
                    {
                        maxLen = curPalindromicStrMax;
                        start = i;
                    }
                }
            }
        }

        char *ret = malloc(sizeof(char)*(maxLen+1));
        memcpy(ret, &s[start], sizeof(char)*maxLen);
        ret[maxLen] = '\0';
        return ret;
    }
}
