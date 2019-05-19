/**

122. Best Time to Buy and Sell Stock II [E]
Ref: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

 */
int maxProfit(int* prices, int pricesSize)
{

	int ret = 0;
	for (int i = 1; i < pricesSize; i++)
	{
		if (prices[i] > prices[i-1])
		{
			ret += prices[i]-prices[i-1];
		}
	}

	return ret;
}
