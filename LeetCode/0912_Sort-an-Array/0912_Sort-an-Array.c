/**

912. Sort an Array [M]
Ref: https://leetcode.com/problems/sort-an-array/

 */

void merge(int *ret, int *nums, int start1, int end1, int start2, int end2)
{
	int idx = start1;
	int i = start1;
	int j = start2;
	while (i <= end1 && j <= end2)
	{
		if (nums[i] < nums[j])
		{
			ret[idx] = nums[i];
			i++;
			idx++;
		} else if (nums[i] > nums[j])
		{
			ret[idx] = nums[j];
			j++;
			idx++;
		} else
		{
			ret[idx] = nums[i];
			ret[idx+1] = nums[j];
			i++;
			j++;
			idx+=2;
		}        
	}

	while (i <= end1)
	{
		ret[idx] = nums[i];
		i++;
		idx++;
	}
	while (j <= end2)
	{
		ret[idx] = nums[j];
		j++;
		idx++;
	}
	memcpy(&(nums[start1]), &(ret[start1]), sizeof(int)*(end2-start1+1));
}

void mergeSort(int *ret, int *nums, int head, int tail)
{
	if (head >= tail)
	{
		return;
	}
	int mid = head+(tail-head)/2;
	mergeSort(ret, nums, head, mid);
	mergeSort(ret, nums, mid+1, tail);
	merge(ret, nums, head, mid, mid+1, tail);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize)
{
	int *ret = malloc(sizeof(int)*numsSize);
	*returnSize = numsSize;
	memcpy(ret, nums, sizeof(int)*numsSize);
	mergeSort(ret, nums, 0, numsSize-1);

	return ret;
}
