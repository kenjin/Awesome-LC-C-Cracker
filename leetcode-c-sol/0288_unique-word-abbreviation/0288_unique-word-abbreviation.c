typedef struct hashT HASH;

struct hashInfo
{
	int ctr;
	int len;
	char *str;       
};

struct hashT
{
	int size;
	int mod;
	struct hashInfo **arr;
};

typedef struct 
{
	HASH *h;
	HASH *h_original;
} ValidWordAbbr;

int hash(HASH *obj, char *str, int keyLen)
{
	size_t hash = 5381;
	while (*str)
	{
		hash = 33 * hash ^ (unsigned char) *str++;
	}
	return hash % obj->mod;
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
		newInfo->ctr = 0;
		obj->arr[x] = newInfo;
	}
	return obj;
}

void addHash(HASH *ht, char *key) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index]->ctr != 0)
	{
		if (!strncmp(key, ht->arr[index]->str, keyLen))
		{
			ht->arr[index]->ctr += 1;
			return;
		}
		index++;
		index %= ht->size;
	}

	ht->arr[index]->ctr = 1;
	ht->arr[index]->str = calloc(keyLen+1, sizeof(char));
	ht->arr[index]->len = keyLen;
	strcpy(ht->arr[index]->str, key);
}

int findHash(HASH *ht, char *key) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);    
	while (ht->arr[index]->ctr != 0) 
	{
		if (ht->arr[index]->len == keyLen && !strncmp(ht->arr[index]->str, key, keyLen))
		{
			return ht->arr[index]->ctr;
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
		free(ht->arr[i]->str);
		free(ht->arr[i]);
	}
	free(ht->arr);
	free(ht);
}

/* MUST need to free the ret pointer */
char* createAbbreviation(char *str)
{
	int len = strlen(str);
	char *ret = calloc(len+1, sizeof(char));

	if (len > 2)
	{
		sprintf(ret, "%c%d%c", str[0], len-2, str[len-1]);
	} else
	{
		strcpy(ret, str);
	}    
	return ret;
}

ValidWordAbbr* validWordAbbrCreate(char ** dictionary, int dictionarySize) 
{
	ValidWordAbbr *obj = calloc(1, sizeof(ValidWordAbbr));
	obj->h = createHash(dictionarySize+1);
	obj->h_original = createHash(dictionarySize+1);
	for (int i = 0; i < dictionarySize; i++)
	{  
		char *tmp = createAbbreviation(dictionary[i]);        
		if (findHash(obj->h_original, dictionary[i]) == -1)
		{
			addHash(obj->h, tmp);
			addHash(obj->h_original, dictionary[i]);
		}
		free(tmp);
	}

	return obj;
}

bool validWordAbbrIsUnique(ValidWordAbbr* obj, char * word) 
{
	if (obj->h_original->size == 0)
	{
		return true;
	}

	int len = strlen(word);
	char *tmp = createAbbreviation(word);
	int findRet = findHash(obj->h, tmp);
	free(tmp);

	if ((-1 == findRet) || // The first word
			(1 == findRet && -1 != findHash(obj->h_original, word))) // The unique abbreviation and is in the dict
	{
		return true;
	} else
	{
		return false;
	}
}

void validWordAbbrFree(ValidWordAbbr* obj) 
{
	releaseHash(obj->h);
	releaseHash(obj->h_original);
	free(obj);
	return;    
}

/**
 * Your ValidWordAbbr struct will be instantiated and called as such:
 * ValidWordAbbr* obj = validWordAbbrCreate(dictionary, dictionarySize);
 * bool param_1 = validWordAbbrIsUnique(obj, word);

 * validWordAbbrFree(obj);
 */
