#define MAX_TRIP   1001

bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity)
{
	int record[MAX_TRIP] = {0};

	for (int i = 0; i < tripsSize; i++)
	{
		for (int j = trips[i][1]; j < trips[i][2]; j++)
		{
			record[j] += trips[i][0];
			if (record[j] > capacity)
			{
				return false;
			}
		}
	}

	return true;
}


