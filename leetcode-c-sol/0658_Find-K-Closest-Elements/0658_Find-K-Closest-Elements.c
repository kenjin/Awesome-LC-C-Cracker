/**

658. Find K Closest Elements [M]

Ref: https://leetcode.com/problems/find-k-closest-elements/

 */

int binarySearchClosest(int *arr, int arrSize, int head, int tail, int target)
{
	if (head >= arrSize)
	{
		return (arrSize-1);
	}
	if (tail < 0)
	{
		return 0;
	}
	if (head > tail)
	{
		return (abs(arr[head]-target) < abs(arr[tail]-target) ? head : tail);
	}

	int mid = head + (tail-head)/2;    
	if (target < arr[mid])
	{
		return binarySearchClosest(arr, arrSize, head, mid-1, target);
	} else if (target > arr[mid])
	{
		return binarySearchClosest(arr, arrSize, mid+1, tail, target);
	} else
	{
		return mid;
	}   
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize)
{
	if (k == 0)
	{
		return NULL;
	}

	/* O(logN) */
	int result = binarySearchClosest(arr, arrSize, 0, arrSize-1, x);

	int head = result;
	int tail = result+1;
	/* Merge and Compare */
	int *ret = malloc(sizeof(int)*k);
	*returnSize = k;
	int count = 0;

	/* O(k) */
	while (count < k)
	{
		/* Check the limit of head/tail */
		if (head < 0 || tail >= arrSize )
		{
			if (head < 0)
			{
				tail++;
			} else
			{
				head--;
			}
		} else
		{
			if (abs(arr[head] - x) <= abs(arr[tail] - x))
			{
				head--;
			} else
			{
				tail++;
			}
		}
		count++;
	}

	/* Adjust head */
	head++;

	for (int i = 0; i < (*returnSize); i++)
	{
		ret[i] = arr[head+i];
	}
	return ret;
}


