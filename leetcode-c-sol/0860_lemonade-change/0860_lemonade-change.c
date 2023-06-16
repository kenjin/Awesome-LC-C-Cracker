
bool lemonadeChange(int* bills, int billsSize)
{
	int ctr[3] = {0};
	for (int i = 0; i < billsSize; i++)
	{
		ctr[bills[i]/10] += 1;
		if (bills[i] == 10)
		{
			ctr[0] -= 1;
		} else if (bills[i] == 20)
		{
			if (ctr[1] > 0)
			{
				ctr[0] -= 1;
				ctr[1] -= 1;                
			} else
			{
				ctr[0] -= 3;
			}
		}
		if (ctr[0] < 0)
		{
			return false;
		}
	}

	return true;
}

