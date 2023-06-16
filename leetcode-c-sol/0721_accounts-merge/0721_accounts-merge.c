#define TYPE_EMPTY          (-1)
#define MAIL_SIZE           (31)

typedef struct hashInfo
{
	int idx;
	char str[MAIL_SIZE];       
}INFO;

typedef struct hashT
{
	int size;
	int mod;
	INFO **arr;
}HASH;

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
		INFO *newInfo = calloc(1, sizeof(INFO));
		newInfo->idx = TYPE_EMPTY;
		obj->arr[x] = newInfo;
	}
	return obj;
}

int addHash(HASH *ht, char *key, int idx) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index]->idx != TYPE_EMPTY) 
	{
		if (!strcmp(key, ht->arr[index]->str))
		{ 
			return TYPE_EMPTY;
		}
		index++;
		index %= ht->size;
	}

	ht->arr[index]->idx = idx;
	strncpy(ht->arr[index]->str, key, keyLen);
	return idx;
}

int findHash(HASH *ht, char *key) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index]->idx != TYPE_EMPTY) 
	{
		if (!strncasecmp(ht->arr[index]->str, key, keyLen))
		{
			return ht->arr[index]->idx;
		}
		index++;
		index %= ht->size;
	}
	return TYPE_EMPTY;
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

int compare(const void *a, const void *b)
{
	const char *s1 = *(char **)a;
	const char *s2 = *(char **)b;

	return (strcmp(s1, s2));
}

int findSet(int *parent, int i) 
{
	// -1 means the root is set[i] itself
	if (parent[i] == -1) 
	{
		return i;
	}
	return findSet(parent, parent[i]); 
} 

void unionSet(int *parent, int x, int y) 
{ 
	int xSet = findSet(parent, x); 
	int ySet = findSet(parent, y); 

	// Ignore the same existed root
	if (xSet == ySet && xSet != -1)
	{
		return;
	}
	parent[xSet] = ySet;
} 

char *** accountsMerge(char *** accounts, int accountsSize, int* accountsColSize, int* returnSize, int** returnColumnSizes)
{
	// Disjoint Set
	int *set = malloc(sizeof(int)*accountsSize);
	for (int i = 0; i < accountsSize; i++)
	{
		set[i] = -1;
	}

	HASH *h = createHash(accountsSize*10);
	for (int i = 0; i < accountsSize; i++)
	{
		for (int j = 1; j < accountsColSize[i]; j++)
		{
			int findRet = findHash(h, accounts[i][j]);
			if (TYPE_EMPTY != findRet)
			{
				// Union Set !
				unionSet(set, findRet, i);
			}            
		}
		for (int j = 1; j < accountsColSize[i]; j++)
		{
			addHash(h, accounts[i][j], i);
		}
	}
	releaseHash(h);

	HASH *h2 = createHash(accountsSize*10);
	char ***ret = malloc(sizeof(char **));
	*returnColumnSizes = malloc(sizeof(int));
	int retCtr = 0;

	// Simple HashSet to find the ret index
	int *update = malloc(accountsSize*sizeof(int));
	for (int i = 0; i < accountsSize; i++)
	{
		update[i] = TYPE_EMPTY;
	}

	for (int i = 0; i < accountsSize; i++)
	{
		int root = findSet(set, i);
		int updateIdx = update[root];
		int colCtr;
		if (TYPE_EMPTY == update[root])
		{
			ret = realloc(ret, sizeof(char**)*(retCtr+1));
			*returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*(retCtr+1));
			// Add name string
			ret[retCtr] = malloc(sizeof(char *));
			ret[retCtr][0] = calloc(MAIL_SIZE, sizeof(char));
			strcpy(ret[retCtr][0], accounts[i][0]);

			updateIdx = retCtr;
			update[root] = updateIdx; // Update ret idx 
			retCtr++; // Increase return size
			colCtr = 1;            
		} else
		{
			colCtr = (*returnColumnSizes)[updateIdx];
		}

		for (int j = 1; j < accountsColSize[i]; j++)
		{
			if (TYPE_EMPTY == findHash(h2, accounts[i][j]))
			{
				ret[updateIdx] = realloc(ret[updateIdx], sizeof(char *)*(colCtr+1));
				ret[updateIdx][colCtr] = calloc(MAIL_SIZE, sizeof(char));
				strcpy(ret[updateIdx][colCtr], accounts[i][j]);
				addHash(h2, accounts[i][j], i);
				colCtr ++;
			}
		}

		(*returnColumnSizes)[updateIdx] = colCtr;
	}

	// Sort by the email string
	for (int i = 0; i < retCtr; i++)
	{
		qsort(&(ret[i][1]), (*returnColumnSizes)[i]-1, sizeof(char *), compare);
	}

	free(update);
	free(set);
	releaseHash(h2);

	*returnSize = retCtr;
	return ret;
}


