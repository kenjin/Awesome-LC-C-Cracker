typedef struct 
{
	int k;
	int heapSize;
	int lastIdx;
	int *minHeap;
} KthLargest;

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) 
{
	KthLargest *obj = malloc(sizeof(KthLargest));
	obj->k = k;
	// create a min heap, and the max size is k
	obj->minHeap = malloc(sizeof(int)*k);
	obj->lastIdx = -1;

	if (numsSize > k)
	{
		// Add the first k elements to create min heap
		memcpy(obj->minHeap, nums, sizeof(int)*k);
		obj->lastIdx = k-1;
		heapify(obj->minHeap, obj->lastIdx);
		// If the remaining element is bigger than root
		// Replace the root and adjust for this node 
		// (No need to do fully heapify) 
		for (int i = k; i < numsSize; i++)
		{
			if (nums[i] > obj->minHeap[0])
			{
				obj->minHeap[0] = nums[i];
				adjustHeap(obj->minHeap, 0, obj->lastIdx);
			}
		}
	} else
	{
		memcpy(obj->minHeap, nums, sizeof(int)*numsSize);
		obj->lastIdx = numsSize-1; 
		heapify(obj->minHeap, obj->lastIdx);
	}

	return obj;
}

void heapify(int *nums, int lastIdx)
{
	for (int i = (lastIdx-1)/2; i >= 0; i--)
	{
		adjustHeap(nums, i, lastIdx);
	}
}

void adjustHeap(int *nums, int curParent, int lastIdx)
{
	int leftChild = curParent*2+1;
	int rightChild = curParent*2+2;
	int min = curParent;
	if (leftChild <= lastIdx && nums[leftChild] < nums[min])
	{
		min = leftChild;
	}
	if (rightChild <= lastIdx && nums[rightChild] < nums[min])
	{
		min = rightChild;
	}

	if (min != curParent)
	{
		int tmp = nums[min];
		nums[min] = nums[curParent];
		nums[curParent] = tmp;
		adjustHeap(nums, min, lastIdx);
	}
}

int kthLargestAdd(KthLargest* obj, int val) 
{  
	if (obj->lastIdx < (obj->k - 1))
	{
		obj->lastIdx += 1;
		obj->minHeap[obj->lastIdx] = val;
		heapify(obj->minHeap, obj->lastIdx);
	} else  // (obj->lastIdx == obj->k) 
	{
		if (val > obj->minHeap[0])
		{
			// replace the root value (min)
			obj->minHeap[0] = val;
			adjustHeap(obj->minHeap, 0, obj->lastIdx);
		}
	}
	return obj->minHeap[0];
}

void kthLargestFree(KthLargest* obj) 
{
	free(obj->minHeap);
	free(obj);
}

/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);

 * kthLargestFree(obj);
 */
