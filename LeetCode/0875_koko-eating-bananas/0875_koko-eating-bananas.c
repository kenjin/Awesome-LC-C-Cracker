
int minEatingSpeed(int* piles, int pilesSize, int H)
{
	int head = 1;
	int tail = 1e9;
	while (head < tail)
	{
		int mid = (tail-head)/2 + head;
		int ctr = 0;
		for (int x = 0; x < pilesSize; x++)
		{
			ctr += (piles[x] + mid - 1) / mid;
		}        
		if (ctr > H)
		{
			head = mid+1;            
		} else
		{
			tail = mid;
		}
	}

	return tail;
}

