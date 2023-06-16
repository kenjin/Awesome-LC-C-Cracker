/**
51. N-Queens

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.
Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

Example:

Input: 4
Output: [
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]

Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.
*/

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

void checkQueen(int N, int i, int *ans, char *col_conf, char *backslash_conf, 
				char *slash_conf, char ****ret, int *returnSize)
{
	if (i >= N)
	{
		*returnSize += 1;

		*ret = (char ***)realloc(*ret, sizeof(char **) * (*returnSize));
		char **tmp = malloc(sizeof(char *) * N);
		for (int x = 0; x < N; x++)
		{
			tmp[x] = calloc(N+1, sizeof(char) * (N+1)); // Remember set N+1 to '\0' for the end of string
			for (int y = 0; y < N; y++)
			{
				if (ans[x] == y)
				{
					tmp[x][y] = 'Q';
				} else
				{
					tmp[x][y] = '.';
				}
			}
		}
		(*ret)[(*returnSize)-1] = (char **)tmp;
	}

	for (int j = 0; j < N; j++)
	{
		if (col_conf[j] || backslash_conf[i-j+N] || slash_conf[i+j])
		{
			continue;
		}
		ans[i] = j;
		col_conf[j] = backslash_conf[i-j+N] =slash_conf[i+j] = 1;
		checkQueen(N, i+1, ans, col_conf, backslash_conf, slash_conf, ret, returnSize);
		col_conf[j] = backslash_conf[i-j+N] =slash_conf[i+j] = 0;
	}

}

char*** solveNQueens(int n, int* returnSize) {

	if (n < 1)
	{
		return NULL;
	}

	int *ans = calloc(n, sizeof(int));
	char *col_conf = calloc(n, sizeof(char));
	char *backslash_conf = calloc(n*2, sizeof(char));
	char *slash_conf = calloc(n*2, sizeof(char));

	char ***ret = malloc(sizeof(char **));
	*returnSize = 0;
	checkQueen(n, 0, ans, col_conf, backslash_conf, slash_conf, &ret, returnSize);  

	free(ans);
	free(col_conf);
	free(backslash_conf);
	free(slash_conf);
	return ret;
}
