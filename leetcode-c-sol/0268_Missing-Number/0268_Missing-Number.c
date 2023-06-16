
int missingNumber(int* nums, int numsSize)
{
	int ret = ((1+numsSize)*numsSize)/2;
	for (int i = 0; i < numsSize; i++)
	{
		ret -= nums[i];
	}
	return ret;
}
