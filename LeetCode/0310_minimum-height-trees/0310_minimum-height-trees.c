#define EDGE_SIZE_UNIT  500

typedef struct
{
	int cur;
	int ctr;
	int *arr;
} DATA;

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMinHeightTrees(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize)
{
	while (n <= 2)
	{
		*returnSize = n;
		int *ret = malloc(sizeof(int)*n);
		for (int i = 0; i < n; i++)
		{
			ret[i] = i;
		}
		return ret;
	}

	DATA *s = calloc(n, sizeof(DATA));
	for (int i = 0; i < n; i++)
	{
		s[i].arr = malloc(sizeof(int));
	}

	for (int i = 0; i < edgesSize; i++)
	{
		if (s[edges[i][0]].ctr % EDGE_SIZE_UNIT == 0)
		{
			s[edges[i][0]].arr = realloc(s[edges[i][0]].arr, (EDGE_SIZE_UNIT+s[edges[i][0]].ctr)*sizeof(int));
		} 

		if (s[edges[i][1]].ctr % EDGE_SIZE_UNIT == 0)
		{
			s[edges[i][1]].arr = realloc(s[edges[i][1]].arr, (EDGE_SIZE_UNIT+s[edges[i][1]].ctr)*sizeof(int));            
		}

		s[edges[i][0]].arr[s[edges[i][0]].ctr] = edges[i][1];
		s[edges[i][0]].ctr += 1;
		s[edges[i][1]].arr[s[edges[i][1]].ctr] = edges[i][0];
		s[edges[i][1]].ctr += 1;
	}

	int *chk = malloc(sizeof(int)*n);
	int chkCtr = 0;
	for (int i = 0; i < n; i++)
	{
		s[i].cur = s[i].ctr;
		if (s[i].ctr == 1)
		{
			chk[chkCtr] = i;
			chkCtr++;
		}
	}

	// Handle Leaf Node
	int totalNodeCtr = n;
	while (totalNodeCtr > 2)
	{
		int maxCtr = chkCtr;
		chkCtr = 0;
		for (int i = 0; i < maxCtr; i++)
		{
			totalNodeCtr--;
			int rmNode;
			for (int x = 0; x < s[chk[i]].ctr; x++)
			{                
				rmNode = s[chk[i]].arr[x];                
				if (s[rmNode].ctr > 0)
				{                    
					break;
				}                
			}
			s[rmNode].cur -= 1;
			s[chk[i]].ctr = 0;

			if (s[rmNode].cur == 1)
			{
				chk[chkCtr] = rmNode;
				chkCtr++;
			}
		}
	}

	int *ret = malloc(sizeof(int)*chkCtr);
	for (int i = 0; i < chkCtr; i++)
	{
		ret[i] = chk[i];
	}

	free(chk);
	for (int i = 0; i < n; i++)
	{
		if (NULL != s[i].arr)
		{
			free(s[i].arr);
		}
	}
	free(s);
	*returnSize = chkCtr;
	return ret;    
}
