typedef struct hashT HASH;

struct hashInfo
{
	int idx;
	int len;
	char str[101];       
};

struct hashT
{
	int size;
	int mod;
	struct hashInfo **arr;
};

int hash(HASH *obj, char *str, int keyLen)
{
	size_t hash = 5381;
	while (*str)
	{
		hash = 33 * hash ^ (unsigned char) *str++;
	}
	return hash % obj->size;
}

HASH* createHash(int size)
{
	HASH *obj = malloc(sizeof(HASH));
	obj->size = size;
	obj->mod = size;
	obj->arr = malloc(sizeof(struct hashInfo)*(size));
	for (int x = 0; x < size; x++)
	{
		struct hashInfo *newInfo = calloc(1, sizeof(struct hashInfo));
		newInfo->idx = -1;
		obj->arr[x] = newInfo;
	}
	return obj;
}

int addHash(HASH *ht, char *key, int val) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index]->idx != -1) 
	{
		index++;
		index %= ht->size;
	}

	ht->arr[index]->idx = val;
	ht->arr[index]->len = keyLen; 
	strncpy(ht->arr[index]->str, key, keyLen);

	return val;
}

int findHash(HASH *ht, char *key) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index]->idx != -1) 
	{
		if (!strncmp(ht->arr[index]->str, key, keyLen))
		{
			return ht->arr[index]->idx;
		}
		index++;
		index %= ht->size;
	}
	return -1;
}

void releaseHash(HASH *ht)
{
	for (int i = 0; i < ht->size; i++)
	{
		free(ht->arr[i]);
	}
	free(ht->arr);
	free(ht);
}

bool DFS(double **data, int size, char *visited, int head, int tail, double *res)
{   
	for (int i = 0; i < size; i++)
	{        
		if (data[head][i] < 0 || visited[i])
		{
			continue;
		}
		if (i == tail)
		{
			*res *= data[head][i];
			return true;
		}

		visited[head] = 1;
		if (DFS(data, size, visited, i, tail, res))
		{
			*res *= data[head][i];
			return true;
		}
		visited[head] = 0;
	}

	return false;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double* calcEquation(char *** equations, int equationsSize, int* equationsColSize, double* values, int valuesSize, char *** queries, int queriesSize, int* queriesColSize, int* returnSize)
{
	int larger = (equationsSize > queriesSize ? equationsSize*2 : queriesSize*2);
	HASH *h = createHash(larger);
	// Use **data to display the graph via adjacency matrix
	double **data = malloc(sizeof(double *)*equationsSize*2);
	for (int i = 0; i < equationsSize*2; i++)
	{
		data[i] = malloc(sizeof(double)*equationsSize*2);
	}
	for (int i = 0; i < equationsSize*2; i++)
	{
		for (int j = 0; j < equationsSize*2; j++)
		{
			data[i][j] = -1.0;
		}
	}

	int ctr = 0;
	for (int i = 0; i < equationsSize; i++)
	{
		int src = findHash(h, equations[i][0]);
		int dst = findHash(h, equations[i][1]);
		if (-1 == src)
		{            
			src = addHash(h, equations[i][0], ctr);
			ctr++;
		}
		if (-1 == dst)
		{
			dst = addHash(h, equations[i][1], ctr);
			ctr++;
		}
		data[src][dst] = values[i];
		data[dst][src] = 1 / values[i];
	}

	double *ret = malloc(sizeof(double)*queriesSize);
	char *visited = calloc(equationsSize*2, sizeof(char));
	for (int i = 0; i < queriesSize; i++)
	{        
		int head = findHash(h, queries[i][0]);
		int tail = findHash(h, queries[i][1]);
		double res = 1;
		if (-1 == head || -1 == tail)
		{
			ret[i] = -1.0;
		} else if (head == tail)
		{
			ret[i] = 1.0;
		} else if (false == DFS(data, ctr, visited, head, tail, &res))
		{
			ret[i] = -1.0;
		} else
		{
			ret[i] = res;
		}
		memset(visited, 0, sizeof(char)*equationsSize*2);
	}


	*returnSize = queriesSize;
	for (int i = 0; i < equationsSize*2; i++)
	{
		free(data[i]);
	}
	free(data);
	releaseHash(h);
	return ret;
}

