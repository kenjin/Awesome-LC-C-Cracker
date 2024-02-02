int integerBreak(int n)
{
   if (n == 2)
      return 1;
   else if (n == 3)
      return 2;

   int *dp = malloc(sizeof(int)*(n + 1));
   dp[1] = 1;
   dp[2] = 2;
   dp[3] = 3;

   for (int x = 4; x <= n; x++) {
      int max = -1;
      for (int i = 1; i <= (x >> 1); i++) {
         int tmp = dp[i] * dp[x-i];
         max = (max > tmp ? max : tmp);
      }
      dp[x] = max;
   }

   int ret = dp[n];
   free(dp);
   return ret;
}
