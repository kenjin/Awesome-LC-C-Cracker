#define MALLOC_SIZE_UNIT (500)

int compare(const void *a, const void *b)
{
	int n1 = *(int *)a;
	int n2 = *(int *)b;

	return n1 - n2;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes)
{
	if (numsSize < 4)
	{
		*returnSize = 0;
		return NULL;
	}

	qsort(nums, numsSize, sizeof(int), compare);

	int** ret = (int**)malloc(sizeof(int *)*MALLOC_SIZE_UNIT);
	*returnColumnSizes = malloc(sizeof(int)*MALLOC_SIZE_UNIT);
	int retCtr = 0;

	for (int i = 0; i < numsSize-3; i++)
	{
		if (i > 0 && nums[i] == nums[i-1])
		{
			continue; //avoid redundant traversal by isolating the duplicates;
		}
		int tmpTarget = target - nums[i];
		for (int x = i+1; x <= numsSize-3; x++)
		{
			if (x > (i+1) && nums[x] == nums[x-1])
			{
				continue; //avoid redundant traversal by isolating the duplicates;
			}

			int sum = tmpTarget - nums[x];
			int left = x+1;
			int right = numsSize-1;
			while (left < right)
			{
				if (nums[left] + nums[right] == sum)
				{
					ret[retCtr] = malloc(sizeof(int)*4);
					(*returnColumnSizes)[retCtr] = 4;
					ret[retCtr][0] = nums[i];
					ret[retCtr][1] = nums[x];
					ret[retCtr][2] = nums[left];
					ret[retCtr][3] = nums[right];
					retCtr++;
					if (retCtr % MALLOC_SIZE_UNIT == 0)
					{
						ret = realloc(ret, sizeof(int **)*(retCtr+MALLOC_SIZE_UNIT));
						*returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*(retCtr+MALLOC_SIZE_UNIT));
					}
					left++;
					while (nums[left] == nums[left-1] && left < right)
					{
						left++;
					}
				} else if (nums[left] + nums[right] < sum)
				{
					left++;
				} else
				{
					right--;
				}
			}
		}
	}

	*returnSize = retCtr;    
	return ret;
}

