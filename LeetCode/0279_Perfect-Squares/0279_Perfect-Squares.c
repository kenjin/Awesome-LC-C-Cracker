/**
279. Perfect Squares [Medium]

Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.


 */

int numSquares(int n){

    /* dp[i]: recored the least number of perfect square numbers sum to i */
    int dp[n+1];

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 1; i <= n; i++)
    {
        int num = 1;
        int num_square = num*num;
        int min = i;
        while (num_square <= i)
        {
            /* if i equal to num_square => dp[0], it means that only require one square number */
            int tmp = 1 + dp[i-num_square];
            if (tmp < min)
            {
                min = tmp;
            }
            num++;
            num_square = num * num;
        }
        dp[i] = min;
    }

    return dp[n];
}
