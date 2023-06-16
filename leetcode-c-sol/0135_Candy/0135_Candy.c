int candy(int* ratings, int ratingsSize)
{    
	int ret = 1;
	int ctr = 1;    // Candy Counter
	int dec = 0;    // count the continuous decrement
	int max;        // use to record peak point when forcing decrement
	char preNotSmaller = 0;     // record the previous condition is ">" or "="

	for (int i = 1; i < ratingsSize; i++)
	{
		if (ratings[i] >= ratings[i-1])
		{
			preNotSmaller = 1;
			ctr = (ratings[i] == ratings[i-1] ? 1 : ctr+1);   
		} else 
		{            
			if (preNotSmaller)
			{
				max = ctr;
				ctr = 1;
				dec = -1;
				preNotSmaller = 0;
			}

			ctr--;
			dec++;
			if (ctr == 0)
			{
				// adjust the peak value
				if (dec+1 == max)
				{
					dec++;
				}
				ret += dec;
				ctr = 1;                    
			}
		} 
		ret += ctr;
	}    
	return ret;
}
