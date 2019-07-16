#define TYPE_EMPTY          (-1)
#define TYPE_BAN            (-2)

typedef struct hashT HASH;
typedef struct dataInfo DATA;

struct dataInfo
{
	int  ctr;
	char str[101]
};

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
		newInfo->idx = TYPE_EMPTY;
		obj->arr[x] = newInfo;
	}
	return obj;
}

void addHash(HASH *ht, char *key, int idx) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index]->idx != TYPE_EMPTY) 
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
	while (ht->arr[index]->idx != TYPE_EMPTY) 
	{
		if (!strncasecmp(ht->arr[index]->str, key, keyLen))
		{
			return ht->arr[index]->idx;
		}
		printf("..\n");
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

char * mostCommonWord(char * paragraph, char ** banned, int bannedSize)
{
	HASH *h = createHash(500);
	DATA d[101];
	int dataSize = 0;

	for (int x = 0; x < bannedSize; x++)
	{
		addHash(h, banned[x], TYPE_BAN);
	}
	// transfer the string to lowercase
	for (int x = 0; x < strlen(paragraph); x++)
	{
		if (paragraph[x] >= 'A' && paragraph[x] <= 'Z')
		{
			paragraph[x] = paragraph[x] - 'A' + 'a';
		}
	}

	char *delim = " ,.!?;:'";
	char *pch;
	pch = strtok(paragraph, delim);
	int maxIdx = 0; // The answer is unique
	while (pch != NULL)
	{
		int ret = findHash(h, pch);           
		if (TYPE_EMPTY == ret)
		{
			d[dataSize].ctr = 1;
			sprintf(d[dataSize].str, "%s", pch);            
			addHash(h, pch, dataSize);
			dataSize++;
		} else if (ret >= 0)
		{
			d[ret].ctr += 1;
			if (d[ret].ctr > d[maxIdx].ctr)
			{
				maxIdx = ret;
			}
		}
		pch = strtok(NULL, delim);
	}      

	releaseHash(h);
	char *ret = calloc(strlen(d[maxIdx].str)+1, sizeof(char));
	strcpy(ret, d[maxIdx].str);    
	return ret;
}


