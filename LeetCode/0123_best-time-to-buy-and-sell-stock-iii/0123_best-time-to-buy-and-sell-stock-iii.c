int maxProfit(int* prices, int pricesSize)
{
	if (pricesSize == 0)
	{
		return 0;
	}

	int *tranOnce = calloc(pricesSize, sizeof(int)*pricesSize);
	int *afterTran = calloc(pricesSize, sizeof(int));
	int minIdx = 0;    
	int maxIdx = pricesSize-1;
	int ret = 0;

	for (int i = 1; i < pricesSize; i++)
	{
		if (prices[i] > prices[minIdx])
		{
			tranOnce[i] = (tranOnce[i-1] > (prices[i] - prices[minIdx]) ? tranOnce[i-1] : (prices[i] - prices[minIdx]));
		}
		minIdx = (prices[minIdx] < prices[i] ? minIdx : i);
	}


	for (int i = pricesSize-2; i >= 0; i--)
	{
		afterTran[i] = (afterTran[i+1] > (prices[maxIdx] - prices[i]) ? afterTran[i+1] : (prices[maxIdx] - prices[i]));
		maxIdx = (prices[maxIdx] > prices[i] ? maxIdx : i);
	}

	// Check the possible max value of twice tranaction
	for (int x = 1; x < pricesSize; x++)
	{
		ret = (ret > tranOnce[x-1] + afterTran[x] ? ret : tranOnce[x-1] + afterTran[x]);
	}

	// Consider one transaction case (tranOnce[7] == afterTran[0])
	ret = ret > afterTran[0] ? ret : afterTran[0];

	free(tranOnce);
	free(afterTran);
	return ret ;
}

