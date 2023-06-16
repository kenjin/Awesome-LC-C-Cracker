typedef struct
{
	int head;
	int tail;
} DATA;

int compare(const void *a, const void *b)
{
	DATA n1 = *(DATA *)a;
	DATA n2 = *(DATA *)b;

	if (n1.head == -1)
	{
		return 1;
	} else if (n2.head == -1)
	{
		return -1;
	} else
	{
		return n1.head - n2.head;
	}
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* partitionLabels(char * S, int* returnSize)
{
	int *ret = malloc(sizeof(int));
	*returnSize = 0;

	// Calculate the start index and end index for each letter
	int len = strlen(S);
	DATA d[26] = {0};
	for (int i = 0; i < 26; i++)
	{
		char cur = 'a' + i;
		int head = -1;
		int tail = -1;

		for (int x = 0; x < len; x++)
		{
			if (S[x] == cur)
			{
				head = (head == -1 ? x : head);
				tail = x;
			}
		}
		d[i].head = head;
		d[i].tail = tail;
	}

	// Sort via start index
	qsort(d, 26, sizeof(DATA), compare);

	int curHead = d[0].head;
	int curTail = d[0].tail;
	int retCtr = 0;
	for (int i = 1; i < 26; i++)
	{
		if (d[i].head == -1)
		{
			break;
		}
		if (d[i].head > curTail)
		{
			ret[retCtr] = curTail - curHead + 1;
			curHead = d[i].head;
			curTail = d[i].tail;         
			retCtr++;
			ret = realloc(ret, sizeof(int)*(retCtr+1));
		} else
		{
			curTail = curTail > d[i].tail ? curTail : d[i].tail;
		}
	}

	ret = realloc(ret, sizeof(int)*(retCtr+1));
	ret[retCtr] = curTail - curHead + 1;
	*returnSize = retCtr+1;
	return ret;
}

