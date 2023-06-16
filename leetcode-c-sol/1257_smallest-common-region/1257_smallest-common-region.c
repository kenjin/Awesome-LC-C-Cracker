#define STR_MAX (21)

typedef struct
{
	int pX;
	int pY;
	int x;
	int y;
} NODE;

typedef struct
{
	int len;
	char str[STR_MAX];
	int idx;
} SET_DATA;

typedef struct
{
	int size;
	SET_DATA *arr;
} HASH;

int hash(HASH *obj, char *str)
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
	obj->arr = calloc(size, sizeof(SET_DATA));
	return obj;
}

void addHash(HASH *ht, char *key, int idx) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key);
	while (ht->arr[index].len != 0) 
	{
		index++;
		index %= ht->size;
	}

	ht->arr[index].len = keyLen;
	strcpy(ht->arr[index].str, key);
	ht->arr[index].idx= idx;
}

int findHash(HASH *ht, char *key) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key);
	while (ht->arr[index].len != 0)
	{
		if (ht->arr[index].len == keyLen &&
				!strcmp(ht->arr[index].str, key))
		{
			return ht->arr[index].idx;
		}
		index++;
		index %= ht->size;
	}
	return -1;
}

void releaseHash(HASH *ht)
{
	free(ht->arr);
	free(ht);
}

char * findSmallestRegion(char *** regions, int regionsSize, int* regionsColSize, char * region1, char * region2)
{
	int maxCol = 0;
	for (int i = 0; i < regionsSize; i++)
	{
		maxCol = maxCol > regionsColSize[i] ? maxCol : regionsColSize[i];
	}

	// Get the parent-child relationship
	NODE *d = malloc(sizeof(NODE)*maxCol*regionsSize);
	HASH *h = createHash(maxCol*regionsSize);
	int ctr = 0, findRet;
	for (int i = 0; i < regionsSize; i++)
	{
		int curParentX = i, curParentY = 0;
		if (-1 == (findRet = findHash(h, regions[i][0])))
		{
			d[ctr].pX = -1;
			d[ctr].pY = -1;            
			d[ctr].x = i;
			d[ctr].y = 0;
			addHash(h, regions[i][0], ctr);
			ctr++;
		} else
		{
			curParentX = d[findRet].x;
			curParentY = d[findRet].y;
		}

		for (int j = 1; j < regionsColSize[i]; j++)
		{ 
			if (-1 != (findRet = findHash(h, regions[i][j])))
			{    
				int parentRowIdx = d[findRet].pX;
				int parentColIdx = d[findRet].pY;
				d[findRet].pX = curParentX;
				d[findRet].pY = curParentY;
			} else
			{
				d[ctr].pX = curParentX;
				d[ctr].pY = curParentY;
				d[ctr].x = i;
				d[ctr].y = j;
				addHash(h, regions[i][j], ctr);
				ctr++;            
			}
		}
	}

	// Check the region1, use result hash(resH) to store the region that have been visisted
	HASH *resH = createHash(maxCol*regionsSize);
	int chk = findHash(h, region1);
	while (d[chk].pX != -1)
	{
		addHash(resH, regions[d[chk].x][d[chk].y], 1);
		chk = findHash(h, regions[d[chk].pX][d[chk].pY]);
	}
	addHash(resH, regions[d[chk].x][d[chk].y], 1);
	// Check the region2, if find from the result hash table, then return smallest common region
	chk = findHash(h, region2);
	while (-1 == findHash(resH, regions[d[chk].x][d[chk].y]))
	{
		chk = findHash(h, regions[d[chk].pX][d[chk].pY]);
	}

	int retX = d[chk].x, retY = d[chk].y;    
	releaseHash(resH);
	releaseHash(h);
	free(d);
	return regions[retX][retY];
}

