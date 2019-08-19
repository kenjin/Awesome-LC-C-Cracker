typedef struct 
{
	int randomMax;
	int size;
	int *sum;
} Solution;

Solution* solutionCreate(int* w, int wSize) 
{
	srand(time(NULL));
	Solution *obj = malloc(sizeof(Solution));
	obj->sum = malloc(sizeof(int)*wSize);
	obj->size = wSize;

	obj->sum[0] = w[0];
	for (int i = 1; i < wSize; i++)
	{
		obj->sum[i] = obj->sum[i-1] + w[i];
	}
	obj->randomMax = obj->sum[wSize-1];

	return obj;
}


int solutionPickIndex(Solution* obj) 
{
	// Get random number
	int target = rand() % obj->randomMax; 

	// Binary Search
	int *n = obj->sum;
	int head = 0, tail = obj->size - 1, mid;
	while (head < tail)
	{
		mid = head + (tail-head)/2;
		if (target >= n[mid])
		{
			head = mid+1;
		} else
		{
			tail = mid;
		}
	}

	return tail;
}

void solutionFree(Solution* obj) 
{
	free(obj->sum);
	free(obj);
}

/**
 * Your Solution struct will be instantiated and called as such:
 * Solution* obj = solutionCreate(w, wSize);
 * int param_1 = solutionPickIndex(obj);

 * solutionFree(obj);
 */

