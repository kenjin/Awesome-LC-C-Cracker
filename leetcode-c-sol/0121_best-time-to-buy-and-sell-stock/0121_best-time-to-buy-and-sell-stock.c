
int maxProfit(int* prices, int pricesSize)
{
	int ret = 0;
	int minIdx = 0;
	for (int i = 0; i < pricesSize; i++)
	{
		if (prices[i] > prices[minIdx])
		{
			ret = (ret > (prices[i] - prices[minIdx]) ? ret : (prices[i] - prices[minIdx]));
		}

		minIdx = (prices[minIdx] < prices[i] ? minIdx : i);    
	}

	return ret;
}

