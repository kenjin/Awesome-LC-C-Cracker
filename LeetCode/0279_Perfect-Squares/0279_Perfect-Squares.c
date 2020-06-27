/**
  279. Perfect Squares [Medium]

  Given a positive integer n, find the least number of perfect square numbers
(for example, 1, 4, 9, 16, ...) which sum to n.

  Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.


 */


int numSquares(int n)
{
    if (n <= 1)
        return n;

    /* dp[i]: recored the least number of perfect square numbers sum to i */
    int *dp = malloc(sizeof(int) * (n + 1));
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int num_square = 1, min = i;
        for (int num = 1; num_square <= i; num++) {
            /* if i equal to num_square => dp[0], it means that only require one
             * square number */
            int tmp = 1 + dp[i - num_square];
            if (tmp < min)
                min = tmp;
            num_square = num * num;
        }
        dp[i] = min;
    }

    int ret = dp[n];
    free(dp);
    return ret;
}
