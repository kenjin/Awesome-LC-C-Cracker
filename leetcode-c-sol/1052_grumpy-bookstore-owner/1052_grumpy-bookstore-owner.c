#define MAX_CUSTOMER_LEN    20000

int maxSatisfied(int* customers, int customersSize, int* grumpy, int grumpySize, int X)
{
	int prefixGrumpySum[MAX_CUSTOMER_LEN] = {0};    

	prefixGrumpySum[0] = (grumpy[0] ? customers[0] : 0);
	int sum = (grumpy[0] ? 0 : customers[0]);
	for (int i = 1; i < customersSize; i++)
	{
		if (grumpy[i])
		{
			prefixGrumpySum[i] = prefixGrumpySum[i-1] + customers[i];            
		} else
		{
			prefixGrumpySum[i] = prefixGrumpySum[i-1];
			sum += customers[i];
		}
	}

	int max = prefixGrumpySum[X-1];
	for (int i = X; i < customersSize; i++)
	{
		int tmp = prefixGrumpySum[i] - prefixGrumpySum[i-X];
		max = max > tmp ? max : tmp;
	}

	return sum+max;
}

