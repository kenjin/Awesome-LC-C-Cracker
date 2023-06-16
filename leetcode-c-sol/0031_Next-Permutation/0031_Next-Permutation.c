
#define SWAP(a,b) { a^=b, b^=a, a^=b; }

void invertNums(int *n, int size)
{
	int head = 0;
	int tail = size-1;
	while (head < tail)
	{
		SWAP(n[head], n[tail]);
		head++;
		tail--;
	}
}

void nextPermutation(int* nums, int numsSize)
{
	if (numsSize < 2)
	{
		return;
	}

	int minIdx = numsSize-1;
	for (int i = 0; i <= (numsSize-2); i++)
	{
		int x = numsSize - 2 - i;
		int y = numsSize - 1 - i;

		// it means that we can get the next greater permutation 
		if (nums[x] < nums[y])
		{
			// Find the minIdx that is greater than nums[x] and is the minimum in subarray (x+1 ~ numsSize-1)
			int minIdx = y;
			for (int j = x+1; j < numsSize; j++)
			{
				if (nums[x] >= nums[j])
				{
					continue;
				} else
				{
					minIdx = nums[j] <= nums[minIdx] ? j : minIdx;
				}
			}
			// swap nums[x] and the nums[minIdx]
			SWAP(nums[x], nums[minIdx]);
			// resursion: subarray(x+1 ~ numsSize-1)
			nextPermutation(&(nums[x+1]), numsSize-(x+1));
			return;
		}
	}

	// rearrange to lowest order
	invertNums(nums, numsSize);
}


