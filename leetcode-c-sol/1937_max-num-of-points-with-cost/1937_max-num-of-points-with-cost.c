#define MAX(a, b) (a > b ? a : b)

long long maxPoints(int** points, int pointsSize, int* pointsColSize)
{
   long long *dp[2], col_sz = pointsColSize[0];
   dp[0] = malloc(sizeof(long long)*col_sz);
   dp[1] = malloc(sizeof(long long)*col_sz);
   
   for (int i = 0; i < col_sz; i++)
      dp[0][i] = points[0][i];
   
   int cur_idx, prev_idx = 0;
   for (int i = 1; i < pointsSize; i++) {
      long long prev = 0;
      cur_idx = prev_idx ^ 1;
      for (int j = 0; j < col_sz; j++) {
         prev = MAX(prev, dp[prev_idx][j]);
         dp[cur_idx][j] = prev + points[i][j];
         prev--;
      }
      
      prev = 0;
      for (int j = col_sz -1 ; j >= 0; j--) {
         prev = MAX(prev, dp[prev_idx][j]);
         dp[cur_idx][j] = MAX(dp[cur_idx][j], points[i][j] + prev);
         prev--;
      }

      prev_idx ^= 1;
   }

   long long res = 0;
   for (int i = 0; i < col_sz; i++)
      res = MAX(dp[prev_idx][i], res);

   free(dp[0]);
   free(dp[1]);
   return res;
}
