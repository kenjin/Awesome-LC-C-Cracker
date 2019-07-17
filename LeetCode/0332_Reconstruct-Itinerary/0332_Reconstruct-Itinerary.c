typedef struct nodeInfo NODE;
struct nodeInfo
{
	char src[4];
	int idx;    // the first index of tickets that "from" is src
	int size;   // the total size of tickets that "from" is src
	NODE *next;
};

typedef struct hash
{
	int bucketSize;
	int mod;
	NODE **bucket;
} HASH;

NODE* createNode()
{
	NODE *newNode = calloc(1, sizeof(NODE));
	newNode->next = NULL;
	return newNode;
}

HASH* createHash(int size)
{
	HASH *obj = malloc(sizeof(HASH));
	obj->bucketSize = size;
	obj->mod = size;
	obj->bucket = malloc(sizeof(NODE*)*size);
	for (int i = 0; i < size; i++)
	{
		obj->bucket[i] = createNode();
	}        
	return obj;
}

void destroyHash(HASH *obj)
{
	for (int i = 0; i < obj->bucketSize; i++)
	{
		NODE *delNode = obj->bucket[i];
		while (delNode != NULL)
		{
			NODE *tmpDel = delNode->next;            
			free(delNode);
			delNode = tmpDel;
		}
	}
	free(obj);
}

int dohash(HASH *obj, char *str, int keyLen)
{
	size_t hash = 5381;
	while (*str)
	{
		hash = 33 * hash ^ (unsigned char) *str++;
	}
	return hash % obj->mod;
}

bool findHash(HASH *obj, char *key, int *ret)
{
	int keyLen = strlen(key);
	int hashIdx = dohash(obj, key, keyLen);
	NODE *tmp = obj->bucket[hashIdx];    
	while (tmp != NULL)
	{
		if (0 == strcmp(tmp->src, key))        
		{
			ret[0] = tmp->idx;
			ret[1] = tmp->size;            
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

void addHash(HASH *obj, char *key, int idx)
{
	int keyLen = strlen(key);
	int hashIdx = dohash(obj, key, keyLen);

	if (obj->bucket[hashIdx]->next == NULL)
	{
		strcpy(obj->bucket[hashIdx]->src, key);
		obj->bucket[hashIdx]->idx =idx;
		obj->bucket[hashIdx]->size = 1;
		obj->bucket[hashIdx]->next = createNode();
	} else
	{
		NODE *tmp = obj->bucket[hashIdx];
		while (tmp->next != NULL)
		{
			if (0 == strcmp(tmp->src, key))
			{
				tmp->size++;
				return;
			}
			tmp = tmp->next;
		}
		strcpy(tmp->src, key);
		tmp->idx = idx;
		tmp->size = 1;
		tmp->next = createNode();
	}
}

bool IATA_dfs(HASH *h, char ***tickets, char **ret, int retSize, char *target, int idx, char *check)
{
	if (idx == retSize)
	{        
		return true;
	}

	/*
	 * findRet[0]: first index of tickets that "from" is target
	 * findRet[1]: total size of tickets that "from" is target
	 */
	int findRet[2] = {0};
	if (false == findHash(h, target, findRet))
	{
		return false;
	}

	int i = findRet[0];
	bool found = false;
	while (i < findRet[0]+findRet[1])
	{        
		if (check[i])
		{
			i++;
			continue;
		}
		// update check flag
		check[i] = 1;                
		if (true == IATA_dfs(h, tickets, ret, retSize, tickets[i][1], idx+1, check))
		{            
			found = true;
			break;
		}
		// release check flag
		check[i] = 0;
		i++;
	}
	if (!found)
	{
		return false;
	}

	ret[idx] = calloc(4, sizeof(char));
	strcpy(ret[idx], tickets[i][1]);
	return true;
}


int compare(const void *a, const void *b)
{
	const char **s1 = *(char ***)a;
	const char **s2 = *(char ***)b;

	int ret = strcmp(s1[0], s2[0]);
	if (0 == ret)
	{
		return strcmp(s1[1], s2[1]);
	}
	return ret;
}

char ** findItinerary(char *** tickets, int ticketsSize, int* ticketsColSize, int* returnSize)
{   
	// Sort all tickets pair
	qsort(tickets, ticketsSize, sizeof(char *), compare);

	// Create hash data sructure
	HASH *h = createHash(ticketsSize*2);    

	// Use check pointer to record the tickets[i] is visited(or banned)
	char *check = calloc(ticketsSize, sizeof(char));   

	// Add to hash
	for (int i = 0; i < ticketsSize; i++)
	{
		addHash(h, tickets[i][0], i);
	}

	// Init return variable
	*returnSize = ticketsSize + 1;
	char **ret = malloc(sizeof(char *)*(*returnSize));

	// Init start from "JFK"
	char srcTmp[4] = {0};
	strcpy(srcTmp, "JFK");
	ret[0] = calloc(4, sizeof(char));
	strcpy(ret[0], srcTmp);

	// DFS to update the result
	IATA_dfs(h, tickets, ret, *returnSize, srcTmp, 1, check);

	// Free
	free(check);
	destroyHash(h);
	return ret;
}

