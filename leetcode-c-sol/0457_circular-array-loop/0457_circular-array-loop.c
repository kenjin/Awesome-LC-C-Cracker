
int getNextIdx(int curIdx, int moves, int numsSize)
{
	return (curIdx + moves + numsSize*1001) % numsSize;
}

bool circularArrayLoop(int* nums, int numsSize)
{    
	for (int x = 0; x < numsSize; x++)
	{
		if (nums[x] == 0)
		{
			continue;
		}
		int slow = x;
		int fast = getNextIdx(x, nums[x], numsSize);
		while (nums[x]*nums[fast] > 0 && nums[x]*nums[getNextIdx(fast, nums[fast], numsSize)] > 0)
		{
			if (slow == fast)
			{
				if (fast == getNextIdx(slow, nums[slow], numsSize))
				{
					break;
				}
				return true;
			}
			slow = getNextIdx(slow, nums[slow], numsSize);
			fast = getNextIdx(fast, nums[fast], numsSize);
			fast = getNextIdx(fast, nums[fast], numsSize);
		}        
	}

	return false;
}


