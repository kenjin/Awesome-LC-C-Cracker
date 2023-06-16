/**

52. N-Queens II [H]
Ref: https://leetcode.com/problems/n-queens-ii/

 */

void setQueens(int *ret, int n, int i /* current row */, char *col, char *slash, char *backslash)
{
	if (i == n)
	{
		*ret += 1;
		return;
	}

	/* For current row, check each col is legal or not */
	for (int j = 0; j < n; j++)
	{
		/* Validate the queen */
		if (col[j] || slash[i+j] || backslash[i-j+(n-1)])
		{
			continue;
		}
		/* Mark */
		col[j] = 1;
		slash[i+j] = 1;
		backslash[i-j+(n-1)] = 1;
		/* Find deeper */
		setQueens(ret, n, i+1, col, slash, backslash);
		/* Backtrack */
		col[j] = 0;
		slash[i+j] = 0;
		backslash[i-j+(n-1)] = 0;
	}
}

int totalNQueens(int n)
{
	if (n == 0)
	{
		return 0;
	}

	char col[n], slash[2*n-1], backslash[2*n-1];    
	memset(col, 0, n);
	memset(slash, 0, 2*n-1);
	memset(backslash, 0, 2*n-1);
	int ret = 0;
	setQueens(&ret, n, 0, col, slash, backslash);
	return ret;
}


