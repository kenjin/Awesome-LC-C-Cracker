int numPairsDivisibleBy60(int* time, int timeSize)
{
	int set[60] = {0};
	int ret = 0;

	for (int i = 0; i < timeSize; i++)
	{
		int tmp = time[i] % 60;
		set[tmp] ++;
	}

	for (int x = 1; x <= 29; x++)
	{
		int idx1 = x;
		int idx2 = 60-x;
		ret += set[idx1] * set[idx2];
	}
	// 0 and 30 case
	ret += (set[0]*(set[0]-1)) / 2;
	ret += (set[30]*(set[30]-1)) / 2;
	return ret;
}


