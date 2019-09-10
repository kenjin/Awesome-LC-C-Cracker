typedef struct
{
	int val;
	int repeat;
} NODE;

void swapNode(NODE *a, NODE *b)
{
	NODE tmp = *a;
	*a = *b;
	*b = tmp;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rearrangeBarcodes(int* barcodes, int barcodesSize, int* returnSize)
{    
	int *ret = malloc(sizeof(int)*barcodesSize);
	*returnSize = barcodesSize;

	// Create a hash set, and ignore index "0"
	int set[100002] = {0};    
	NODE *n = malloc(sizeof(NODE)*barcodesSize);
	int nSize = 0;        
	for (int i = 0; i < barcodesSize; i++)
	{
		if (!set[barcodes[i]])
		{
			set[barcodes[i]] = nSize+1;
			n[nSize].val = barcodes[i];
			n[nSize].repeat = 1;
			nSize++;
		} else
		{
			n[ set[barcodes[i]]-1 ].repeat += 1;    
		}
	}

	// Select the most frequent
	int maxIdx = 0;
	for (int i = 1; i < nSize; i++)
	{
		maxIdx = (n[i].repeat > n[maxIdx].repeat ? i : maxIdx);
	}
	swapNode(&(n[maxIdx]), &(n[0]));

	int pos = 0, idx = 0;
	while (idx < nSize)
	{
		ret[pos] = n[idx].val;
		pos += 2;
		if (pos >= barcodesSize)
		{
			pos = 1;
		}

		n[idx].repeat --;
		if (n[idx].repeat == 0)
		{
			idx++;
		}
	}

	free(n);
	return ret;
}

