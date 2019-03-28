/**
	Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? 
	Find all unique triplets in the array which gives the sum of zero.

	Note:
		The solution set must not contain duplicate triplets.

	Example:
		Given array nums = [-1, 0, 1, 2, -1, -4],
		A solution set is:
			[
  				[-1, 0, 1],
    			[-1, -1, 2]
			]
*/

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int partition(int *nums, int start, int end)
{
	int pivot = nums[end];
	int i = start-1, j, tmp;
	for (j = start; j < end; j++)
	{
		if (nums[j] < pivot)
		{
			i++;
			tmp = nums[i];
			nums[i] = nums[j];
			nums[j] = tmp;
		}
	}
	i++;
	tmp = nums[i];
	nums[i] = nums[end];
	nums[end] = tmp;    
	return i;
}

void quicksort(int *nums, int front, int rear)
{
	if (front < rear)
	{
		int pivot = partition(nums, front, rear);
		quicksort(nums, front, pivot-1);
		quicksort(nums, pivot+1, rear);
	}
}

int** threeSum(int* nums, int numsSize, int* returnSize) {

	if (numsSize < 3)
	{
		return NULL;
	}

	// Sort nums
	quicksort(nums, 0, numsSize-1);
	
	int count = 500, left, right, target;
	int** ret = (int**)malloc(sizeof(int*)*count);
	*returnSize = 0;

	for (int i = 0; i < numsSize-2; i++)
	{
		// Avoid the duplicates
		if (i > 0 && nums[i] == nums[i-1])
		{
			continue;
		}

		// Init
		target = (-1)*(nums[i]);
		left = i+1;
		right = numsSize -1;        
		while (left < right)
		{
			if (left > i+1 && nums[left-1] == nums[left])
			{
				left++;
				continue;
			}

			if (nums[left] + nums[right] == target)
			{
				// Avoid the duplicates by checking two latest result
				if ((*returnSize) == 0 || 
						((*returnSize) > 0 && (nums[i] != ret[(*returnSize)-1][0] || nums[left] != ret[(*returnSize)-1][1])))
				{
					*returnSize += 1;
					if ((*returnSize) == count)
					{
						count <<= 1;
						ret = realloc(ret, sizeof(int *) * count);
					}
					ret[*returnSize-1] = (int*)malloc(sizeof(int)*3);
					ret[*returnSize-1][0] = nums[i];
					ret[*returnSize-1][1] = nums[left];
					ret[*returnSize-1][2] = nums[right];
					left++;
				}
			} else if (nums[left] + nums[right] < target)
			{
				left++;
			} else // nums[left] + nums[right] > target
			{
				right--;   
			}

		}
	}
	return ret;
}
