struct domainInfo
{
	int ctr;
	char str[101];
};

typedef struct hashT HASH;
struct hashInfo
{
	int idx;
	char str[101];   
};

struct hashT
{
	int size;
	int mod;
	struct hashInfo **arr;
};

int hash(HASH *obj, char *key, int keyLen) 
{
	int tmp;
	if (keyLen > 2)
	{
		tmp = key[0]*15 + key[1] + key[2];
	} else
	{
		tmp = key[0]*15 + key[1];
	}
	return (tmp*(keyLen) % obj->mod);    
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
		obj->arr[x] = newInfo;
		newInfo->idx = -1;
	}
	return obj;
}

void addHash(HASH *ht, char *key, int idx) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index]->idx != -1) 
	{
		index++;
		index %= ht->size;
	}
	ht->arr[index]->idx = idx;
	strncpy(ht->arr[index]->str, key, keyLen);
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** subdomainVisits(char ** cpdomains, int cpdomainsSize, int* returnSize)
{
	// Prepare the max size of ret
	char **ret = malloc(sizeof(char *)*cpdomainsSize*3);    
	for (int i = 0; i < (cpdomainsSize*3); i++)
	{
		ret[i] = calloc(100, sizeof(char));
	}

	struct domainInfo *dInfo = malloc(sizeof(struct domainInfo)*cpdomainsSize*3);
	int infoNum = 0;
	HASH *h = createHash(400);

	for (int i = 0; i < cpdomainsSize; i++)
	{        
		int idx = 0;
		int ctr = 0;        
		int domainLen = strlen(cpdomains[i]);
		char numDone = 0;
		while (idx < domainLen)
		{
			if (!numDone && cpdomains[i][idx] != ' ')
			{
				ctr = ctr*10 + (cpdomains[i][idx]-'0');
			} else if (cpdomains[i][idx] == ' ' || cpdomains[i][idx] == '.')
			{     
				numDone = 1;
				char *dotStr = &(cpdomains[i][idx+1]);
				int dotStrLen = strlen(dotStr);

				int hashRet = findHash(h, dotStr);
				if ( -1 == hashRet)
				{
					infoNum++;
					dInfo[infoNum-1].ctr = ctr;
					strncpy(dInfo[infoNum-1].str, dotStr, dotStrLen);
					dInfo[infoNum-1].str[dotStrLen] = '\0';
					addHash(h, dotStr, infoNum-1);
				} else
				{
					dInfo[hashRet].ctr += ctr;
				}
			}
			idx++;
		}
	}

	*returnSize = infoNum;
	for (int x = 0; x < infoNum; x++)
	{
		sprintf(ret[x], "%d %s", dInfo[x].ctr, dInfo[x].str);
	}

	free(dInfo);
	releaseHash(h);
	return ret;
}
