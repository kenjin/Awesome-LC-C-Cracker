
int compare(const void *a, const void *b)
{
	int n1 = *(int *)a;
	int n2 = *(int *)b;

	char str1[40] = {0};
	char str2[40] = {0};
	sprintf(str1, "%d%d", n1,n2);
	sprintf(str2, "%d%d", n2,n1);
	return (strcmp(str1, str2) < 0);
}

char * largestNumber(int* nums, int numsSize)
{
	char *ret = calloc(12*numsSize, sizeof(char));
	qsort(nums, numsSize, sizeof(int), compare);

	if (nums[0] == 0)
	{
		ret[0] = '0';        
	} else
	{
		for (int i = 0; i < numsSize; i++)
		{
			char tmp[12] = {0};
			sprintf(tmp, "%d", nums[i]);
			strcat(ret, tmp);        
		}
	}
	return ret;
}

