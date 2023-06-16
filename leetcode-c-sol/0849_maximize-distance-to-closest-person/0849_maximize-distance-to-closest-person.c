
int maxDistToClosest(int* seats, int seatsSize)
{
	int zCtr = 0, max = 0;
	int firstIsZero = (!seats[0] ? 1 : 0);
	for (int i = 0; i < seatsSize; i++)
	{
		if (seats[i])
		{
			int res = (zCtr % 2 == 1 ? zCtr/2+1 : zCtr/2);
			if (firstIsZero)
			{
				res = zCtr;
				firstIsZero = 0;
			}
			max = (res > max ? res : max);          
			zCtr = 0;
		} else
		{
			zCtr ++;
		}
	}
	if (!seats[seatsSize-1])
	{
		max = (zCtr > max ? zCtr : max);
	}

	return max;
}


