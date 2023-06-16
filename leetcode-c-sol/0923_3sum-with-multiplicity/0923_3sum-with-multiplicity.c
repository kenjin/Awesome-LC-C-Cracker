#define MOD_NUM  (1000000000 + 7)

long getCombination(int a, int b)
{
	if (a < b)
	{
		return 0;
	}

	long ret = 1;
	int div = 1;    
	for (int x = 1; x <= b; x++)
	{
		ret *= a;
		a--;
		div *= x;
	}

	return ret/div;
}

int compare(const void *a, const void *b)
{
	int n1 = *(int *)a;
	int n2 = *(int *)b;

	return n1 - n2;
}

int threeSumMulti(int* A, int ASize, int target)
{
	long ret = 0;
	qsort(A, ASize, sizeof(int), compare);

	int *nums = malloc(sizeof(int)*ASize);
	int numsCtr = 0;
	int cnt[101] = {0};
	for (int i = 0; i < ASize; i++)
	{
		if (i == 0 || A[i] != A[i-1])
		{
			nums[numsCtr] = A[i];
			numsCtr ++;
		}
		cnt[A[i]] ++;        
	}

	int check[3] = {0};
	for (int i = 0; i < numsCtr; i++)
	{
		check[0] = nums[i];        
		for (int j = i; j < numsCtr; j++)
		{
			check[1] = nums[j];
			check[2] = target - check[0] - check[1];
			if (check[2] < check[0] || check[2] < check[1])
			{
				continue;
			}                        

			if (check[2] >= 0 && check[2] <=100 && cnt[check[2]])
			{
				long ans = 1;
				int ansCtr = 1;
				for (int x = 1; x < 3; x++)
				{
					if (check[x] != check[x-1])
					{
						ans *= getCombination(cnt[check[x-1]], ansCtr);
						ansCtr = 1;
					} else
					{
						ansCtr++;
					}
				}
				ans *= getCombination(cnt[check[2]], ansCtr);
				ret += ans;                
				ret %= MOD_NUM;
			}
		}
	}

	free(nums);
	return (int)ret;
}

