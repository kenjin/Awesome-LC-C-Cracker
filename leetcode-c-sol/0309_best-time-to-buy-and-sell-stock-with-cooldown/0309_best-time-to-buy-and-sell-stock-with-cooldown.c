#define MAX(a, b) (a > b ? a : b)

int maxProfit(int* prices, int pricesSize)
{
	if (pricesSize <= 1)
	{
		return 0;
	} else if (pricesSize == 2)
	{
		return MAX(0, prices[1] - prices[0]);
	}

	int *buy = malloc(sizeof(int)*pricesSize);
	int *sell = malloc(sizeof(int)*pricesSize);

	buy[0]  = prices[0]*(-1);
	buy[1]  = -1 * (prices[0] < prices[1] ? prices[0] : prices[1]);
	sell[0] = 0;
	sell[1] = (prices[1] - prices[0] > 0 ? prices[1] - prices[0] : 0);    

	for (int i = 2; i < pricesSize; i++)
	{
		buy[i]  = MAX(buy[i-1], sell[i-2] - prices[i]);
		sell[i] = MAX(sell[i-1], buy[i-1] + prices[i]);
	}

	int ret = MAX(buy[pricesSize-1], sell[pricesSize-1]);
	free(buy);
	free(sell);
	return ret;
}

