/***

DP: dp[i][j] represents the number of occurrences of the substring t[0...j] in
the subsequence of s[0...i]. (In other words, it counts how many different ways
there are to delete some elements from s[0...i] to obtain t[0...j].)

At any time, dp[i][j] can be derived from dp[i-1][j] because this problem can be
seen as finding how many different ways there are to delete some elements from
string s to obtain string t. We can understand this as the situation where we
definitely delete the element at index i in string s, turning the problem into
deleting some elements from s[0...i-1] to obtain t[0...j].

- Additionally, when s[i] == t[j], dp[i][j] can also be derived from
dp[i-1][j-1]. This means we don't delete the element at index i in string s
(because s[i] == t[j], and the end is already matched), turning the problem into
deleting some elements from s[0...i-1] to obtain t[0...j-1].

Init: We need to initialize the first row and column of the 2D dp so that
traversal starts from row/col index 1.
- dp[0][0] should check if s[0] equals t[0]. If equal, set to 1; otherwise, set
to 0.
- Except for dp[0][0], all elements in the first row dp[0][j] should be 0
because if s is shorter than t, it cannot satisfy the requirements anyway.
- Except for dp[0][0], the elements dp[i][0] should be initialized to the number
of occurrences of t[0] in the substring s[0...i].

***/

// Constraints:: 1 <= s.length, t.length <= 1000
unsigned long long dp[1000][1000];

int numDistinct(char* s, char* t) {
    int slen = strlen(s), tlen = strlen(t);
    memset(dp, 0, sizeof(dp));

    dp[0][0] = (s[0] == t[0] ? 1 : 0);
    for (int i = 1; i < slen; i++)
        dp[i][0] = (s[i] == t[0] ? dp[i - 1][0] + 1 : dp[i - 1][0]);

    for (int i = 1; i < slen; i++) {
        for (int j = 1; j < tlen; j++) {
            if (s[i] == t[j])
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    return dp[slen - 1][tlen - 1];
}

