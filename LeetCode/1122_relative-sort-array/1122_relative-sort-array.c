
typedef struct dataInfo
{
	int on;
	int ctr;
} DATA;

int compare(const void *a, const void *b)
{
	int n1 = *(int *)a;
	int n2 = *(int *)b;

	return n1 - n2;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize)
{
	int *ret = malloc(sizeof(int)*arr1Size);
	int retCtr = 0;    

	DATA *set = calloc(1001, sizeof(DATA));
	int *exclude = malloc(sizeof(int)*arr1Size);
	int exCtr = 0;
	for (int i = 0; i < arr2Size; i++)
	{
		set[arr2[i]].on = 1;
	}

	for (int i = 0; i < arr1Size; i++)
	{
		if (set[arr1[i]].on)
		{
			set[arr1[i]].ctr += 1;
		} else
		{
			exclude[exCtr] = arr1[i];
			exCtr++;
		}
	}

	for (int i = 0; i < arr2Size; i++)
	{
		if (set[arr2[i]].on)
		{
			for (int j = 0; j < set[arr2[i]].ctr; j++)
			{
				ret[retCtr] = arr2[i];
				retCtr++;
			}
		}
	}

	qsort(exclude, exCtr, sizeof(int), compare);
	for (int i = 0; i < exCtr; i++)
	{
		ret[retCtr] = exclude[i];
		retCtr++;
	}

	*returnSize = retCtr;
	free(set);
	return ret;
}

