
int** generateMatrix(int n, int* returnSize, int** returnColumnSizes)
{
	int **visit = malloc(sizeof(int*)*n);
	int **ret = malloc(sizeof(int*)*n);
	*returnSize = n;
	*returnColumnSizes = malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)
	{
		(*returnColumnSizes)[i] = n;
		visit[i] = calloc(n, sizeof(int));
		ret[i] = malloc(sizeof(int)*n);
	}        

	int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	int r = 0, c = -1, cur = 0;
	int ctr = 1;
	while (ctr <= n*n)
	{   
		r += dir[cur][0];
		c += dir[cur][1];
		while (r < 0 || r >= n || c < 0 || c >= n || visit[r][c])
		{
			r -= dir[cur][0];
			c -= dir[cur][1];
			cur = (cur+1)%4;
			r += dir[cur][0];
			c += dir[cur][1];
		}
		ret[r][c] = ctr;   
		visit[r][c] = 1;
		ctr++;
	}

	for (int i = 0; i < n; i++)
	{
		free(visit[i]);        
	}
	free(visit);

	return ret;
}


