/**

277. Find the Celebrity [M]
Ref: https://leetcode.com/problems/find-the-celebrity/

 */
// Forward declaration of the knows API.
bool knows(int a, int b);

int findCelebrity(int n) 
{
	int record[n];
	memset(record, 0, sizeof(int)*n);

	for (int j = 0; j < n; j++)
	{
		/* I have known somebody */
		if (record[j] == -1)
		{
			continue;
		}
		for (int i = 0; i < n; i++)
		{
			if (i == j)
			{
				continue;
			}

			if (knows(i, j))
			{
				record[j] += 1;
				record[i] = -1;
			}
			/* Check that if I know somebody */
			if (record[j] == n-1)
			{
				int nobody = 0;
				for (int x = 0; x < n; x++)
				{
					if (x == j)
					{
						continue;
					}
					if (knows(j, x))
					{
						nobody = 1;
						break;
					}
				}
				if (!nobody)
				{
					return j;
				}
			}

		}
	}

	return -1;
}
