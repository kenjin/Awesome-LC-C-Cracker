void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int calDistance(int **points, int idx)
{
	return points[idx][0]*points[idx][0] + points[idx][1]*points[idx][1];
}

/* Time Complexity: O(lg n)  => tree height */
void adjustHeap(int *arr, int** points, int nodeIndex, int totalSize)
{
	int rightChild, leftChild, maxIndex;

	leftChild = 2*nodeIndex + 1;
	rightChild = 2*nodeIndex + 2;

	maxIndex = nodeIndex;
	if (leftChild < totalSize)
	{
		int max = calDistance(points, arr[maxIndex]);
		int left = calDistance(points, arr[leftChild]);
		if (max < left)
		{
			maxIndex = leftChild;
		}
	}
	if (rightChild < totalSize)
	{
		int max = calDistance(points, arr[maxIndex]);
		int right = calDistance(points, arr[rightChild]);
		if (max < right)
		{
			maxIndex = rightChild;
		}
	}

	if (nodeIndex != maxIndex)
	{
		swap(&arr[nodeIndex], &arr[maxIndex]);
		adjustHeap(arr, points, maxIndex, totalSize);
	}
} 

void buildHeap(int *arr , int** points, int totalSize)
{
	/* Simple Total: O(n) * O(lg n) = O(n*lgn);  Actual detail is O(n)*/
	for (int i = (totalSize/2)-1; i >= 0; i--)
	{
		adjustHeap(arr, points, i, totalSize);
	} 
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kClosest(int** points, int pointsSize, int* pointsColSize, int K, int* returnSize, int** returnColumnSizes)
{
	// Add the K points index to heap array and build a Max Heap
	int *maxHeap = malloc(sizeof(int)*K);
	for (int i = 0; i < K; i++)
	{
		maxHeap[i] = i;
	}
	buildHeap(maxHeap, points, K);

	// Compare the remaining elements to the root of heap
	for (int i = K; i < pointsSize; i++)
	{
		int curMaxDistance = calDistance(points, maxHeap[0]);
		int tmpDistance = calDistance(points, i);
		if (tmpDistance < curMaxDistance)
		{
			// replace max
			maxHeap[0] = i;
			adjustHeap(maxHeap, points, 0, K);
		}        
	}

	// Complete result
	*returnSize = K;
	int **ret = malloc(sizeof(int*)*K);
	*returnColumnSizes = malloc(sizeof(int)*K);
	for (int i = 0; i < K; i++)
	{
		(*returnColumnSizes)[i] = 2;
		ret[i] = malloc(sizeof(int)*2);

		int cur_idx = maxHeap[i];
		ret[i][0] = points[cur_idx][0];
		ret[i][1] = points[cur_idx][1];
	}

	return ret;
}
