#define MIN(a, b) (a < b ? a : b)

int minFlipsMonoIncr(char * S)
{
	int len = strlen(S);

	int dp0 = 0;
	int dp1 = 0;
	if (len > 0)
	{
		dp0 = (S[0]-'0')^0;
		dp1 = (S[0]-'0')^1;
	}

	for (int i = 1; i < len; i++)
	{
		if (S[i] == '0')
		{
			dp1 = MIN(dp0, dp1) + 1;
		} else
		{
			int odp0 = dp0, odp1 = dp1;
			dp0 = odp0+1;
			dp1 = MIN(odp0, odp1);            
		}
	}

	return dp0 < dp1 ? dp0 : dp1;
}

