#define STR_CODE_SIZE_UNIT 2000

typedef struct gridData
{
	char *strCode;
	int len;
	int size;
	struct gridData *next;
} DATA;

typedef struct hashT
{
	int size;
	int mod;
	DATA **arr;
	int **grid;
} HASH;


void freeGridData(DATA *obj)
{
	free(obj->strCode);
	free(obj);
}

int hash(HASH *obj, char *str)
{    
	size_t hash = 5381;
	while (*str)
	{
		hash = 33 * hash ^ (unsigned char) *str++;
	}
	return hash % obj->size;
}

HASH* createHash(int **grid, int size)
{
	HASH *obj = malloc(sizeof(HASH));
	obj->size = size;
	obj->mod = size;
	obj->arr = calloc(size, sizeof(DATA *));    
	obj->grid = grid;
	return obj;
}

void addHash(HASH *ht, DATA *newOne) 
{
	int index = hash(ht, newOne->strCode);
	DATA *addNode = calloc(1, sizeof(DATA));
	addNode->strCode = calloc(newOne->size, sizeof(char));
	addNode->len = newOne->len;
	addNode->size = newOne->size;    
	strcpy(addNode->strCode, newOne->strCode);

	if (NULL == ht->arr[index])
	{
		ht->arr[index] = addNode;
	} else
	{        
		DATA *checkNode = ht->arr[index];
		DATA *prev = checkNode;
		while (checkNode)
		{
			prev = checkNode;
			checkNode = checkNode->next;
		}
		prev->next = addNode;
	}
}

bool findHash(HASH *ht, DATA *target)
{
	int index = hash(ht, target->strCode);    
	DATA *chk = ht->arr[index];
	while (chk != NULL) 
	{
		if (chk->len == target->len && !strcmp(chk->strCode, target->strCode))
		{
			return true;
		}
		chk = chk->next;
	}
	return false;
}

void releaseHash(HASH *ht)
{
	for (int i = 0; i < ht->size; i++)
	{
		DATA *tmp = ht->arr[i];
		while (tmp)
		{
			DATA *del = tmp->next;
			freeGridData(tmp);
			tmp = del;
		}        
	}
	free(ht->arr);
	free(ht);
}

void numDistinctIslandsHelper(int **grid, int **visited, int rSize, int cSize, int x, int y, DATA *d, int codeX, int codeY)
{
	if (x < 0 || x >= rSize || y < 0 || y >= cSize || !grid[x][y] || visited[x][y])
	{
		return;
	}

	visited[x][y] = 1;

	// Create code string
	char tmpStr[9] = {0}; // Format: -XX_-YY_    
	sprintf(tmpStr, "%d_%d_", codeX, codeY);
	int tmpLen = strlen(tmpStr);    
	if (d->len + tmpLen >= d->size)
	{
		d->size += STR_CODE_SIZE_UNIT;
		d->strCode = realloc(d->strCode, sizeof(char)*d->size);
	}
	strcat(d->strCode, tmpStr);
	d->len += tmpLen;

	int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};    
	for (int i = 0; i < 4; i++)
	{
		numDistinctIslandsHelper(grid, visited, rSize, cSize, x + dir[i][0], y + dir[i][1], d, codeX+dir[i][0], codeY+dir[i][1]);
	}
}

int numDistinctIslands(int** grid, int gridSize, int* gridColSize)
{
	HASH *h = createHash(grid, gridSize*gridColSize[0] + 1);
	int ret = 0;


	int **visited = malloc(sizeof(int *)*gridSize);
	for (int i = 0; i < gridSize; i++)
	{
		visited[i] = calloc(gridColSize[0], sizeof(int));                                
	}

	for (int i = 0; i < gridSize; i++)
	{        
		for (int j = 0; j < gridColSize[0]; j++)
		{
			if (grid[i][j] && !visited[i][j])
			{
				DATA *curData = calloc(1, sizeof(DATA));
				curData->strCode = calloc(STR_CODE_SIZE_UNIT, sizeof(char));
				curData->size = STR_CODE_SIZE_UNIT;                

				numDistinctIslandsHelper(grid, visited, gridSize, gridColSize[0], i, j, curData, 0, 0);
				if (!findHash(h, curData))
				{
					addHash(h, curData);
					ret++;
				}
				freeGridData(curData);
			}
		}
	}

	for (int i = 0; i < gridSize; i++)
	{
		free(visited[i]);
	}    
	free(visited);    
	releaseHash(h);
	return ret;
}

