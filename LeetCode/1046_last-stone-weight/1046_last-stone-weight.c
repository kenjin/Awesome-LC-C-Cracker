void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void heapify(int *arr, int size, int idx)
{
	int leftIdx = idx*2+1;
	int rightIdx = idx*2+2;
	int maxIdx = idx;

	if (rightIdx < size && arr[rightIdx] > arr[maxIdx])
	{
		maxIdx = rightIdx;
	}    
	if (leftIdx < size && arr[leftIdx] > arr[maxIdx])
	{
		maxIdx = leftIdx;
	}

	if (maxIdx != idx)
	{
		swap(&(arr[maxIdx]), &(arr[idx]));
		heapify(arr, size, maxIdx);
	}
}

void createHeap(int *arr, int size)
{
	for (int i = (size-1)/2; i >= 0; i--)
	{
		heapify(arr, size, i);
	}
}

int lastStoneWeight(int* stones, int stonesSize)
{
	createHeap(stones, stonesSize);
	while (stonesSize >= 4)
	{
		int max2 = (stonesSize > 2 && stones[2] > stones[1]) ? 2 : 1;            
		int diff = abs(stones[0] - stones[max2]);

		stones[0] = stones[stonesSize-1];
		stones[max2] = (diff == 0 ? stones[stonesSize-2] : diff);
		stonesSize = (diff == 0 ? stonesSize-2 : stonesSize-1);

		heapify(stones, stonesSize, max2);
		heapify(stones, stonesSize, 0);
	}

	if (stonesSize == 3)
	{
		return abs(stones[0] - stones[1] - stones[2]);        
	} else if (stonesSize == 2)
	{
		return abs(stones[0] - stones[1]);
	} else
	{
		return (stonesSize == 1 ? stones[0] : 0);
	}
}

