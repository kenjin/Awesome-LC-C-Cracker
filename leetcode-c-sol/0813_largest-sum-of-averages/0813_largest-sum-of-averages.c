
double largestSumOfAverages(int* A, int ASize, int K)
{
	double *dp = malloc(sizeof(double)*ASize);
	double sum = 0;
	for (int i = ASize-1; i >= 0; i--)
	{
		sum += A[i];        
		dp[i] = sum / (ASize-i);
	}

	for (int x = 1; x < K-1; x++)
	{
		for (int i = 0; i < ASize; i++)
		{
			double max = 0;
			double tmpSum = 0;
			for (int j = i; j < ASize-1; j++)
			{
				tmpSum += A[j];
				double tmpRes = tmpSum/(j-i+1) + dp[j+1];                
				max = (max > tmpRes ? max : tmpRes);       
			}
			dp[i] = max;
		}        
	}

	double ret = 0;
	if (K > 1)
	{
		// Last round, just handle dp[0] case
		double tmpSum = 0;
		for (int j = 0; j < ASize-1; j++)
		{
			tmpSum += A[j];
			double tmpRes = tmpSum/(j+1) + dp[j+1];            
			ret = (ret > tmpRes ? ret : tmpRes);                
		}
	} else
	{
		ret = dp[0];
	}
	free(dp);
	return ret;
}


