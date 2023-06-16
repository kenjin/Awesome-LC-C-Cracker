#define DATA_SIZE_UNIT 50

typedef struct
{
	int wIdx;
	int bIdx;
}DATA;


int* assignBikes(int** workers, int workersSize, int* workersColSize, int** bikes, int bikesSize, int* bikesColSize, int* returnSize)
{    
	char *assigned = calloc(workersSize, sizeof(char));
	char *occupied = calloc(bikesSize, sizeof(char));
	int *ret = malloc(sizeof(int)*workersSize);
	*returnSize = workersSize;

	DATA *data[2001] = {0};
	for (int i = 0; i < 2001; i++)
	{
		data[i] = malloc(sizeof(DATA)*DATA_SIZE_UNIT);
	}
	int dataCol[2001] = {0};

	for (int i = 0; i < workersSize; i++)
	{
		for (int j = 0; j < bikesSize; j++)
		{
			int dist = abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1]);
			data[dist][dataCol[dist]].wIdx = i;
			data[dist][dataCol[dist]].bIdx = j;
			dataCol[dist] += 1;
			if (0 == dataCol[dist] % DATA_SIZE_UNIT)
			{
				data[dist] = realloc(data[dist], sizeof(DATA)*(dataCol[dist]+DATA_SIZE_UNIT));
			}
		}            
	}

	for (int i = 0; i < 2001; i++)
	{
		for (int x = 0; x < dataCol[i]; x++)
		{
			int curWorker = data[i][x].wIdx;
			int curBike = data[i][x].bIdx;
			if (assigned[curWorker] || occupied[curBike])
			{
				continue;
			}

			ret[curWorker] = curBike;
			assigned[curWorker] = 1;
			occupied[curBike] = 1;
		}
	}    

	free(assigned);
	free(occupied);
	for (int i = 0; i < 2001; i++)
	{
		free(data[i]);
	}
	return ret;
}
