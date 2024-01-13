#define NUM(c) (c - '0')

int numDecodings(char* s)
{
    // sanity check
    if (*s == '0')
        return 0;

    int len = strlen(s), dp0 = 0, dp1 = 1, dp2 = 1;
    for (int i = 1; i < len; i++) {
        dp0 = dp1;
        dp1 = dp2;
        dp2 = 0;
        // 0 - 9
        if (NUM(s[i]) != 0)
            dp2 += dp1;
        // 10 - 26
        if ((NUM(s[i-1])*10 + NUM(s[i])) >= 10 && (NUM(s[i-1])*10 + NUM(s[i])) <= 26)
            dp2 += dp0;
    }

    return dp2;
}
