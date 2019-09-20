#define MAX_WORDS_LEN 1000
typedef struct hashT HASH;

struct hashInfo
{
	int ctr; // Count the chain len
	int len;
	char *str;       
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

void addHash(HASH *ht, char *key, int ctr)
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index]->ctr != 0)
	{
		if (!strncmp(key, ht->arr[index]->str, keyLen))
		{
			return;
		}
		index++;
		index %= ht->size;
	}

	ht->arr[index]->ctr = ctr;
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
	return 0;
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

int getMaxPredecessorLen(HASH *h, char *str)
{
	int len = strlen(str);
	int maxLen = 0;
	char chkStr[17] = {0};
	for (int i = 0; i < len; i++)
	{
		char *str1 = (i > 0 ? str : "");
		char *str2 = (i+1 < len ? &(str[i+1]) : "");
		/* Backup character and set the ith char to '\0' */
		char tmp = str[i];
		str[i] = '\0';
		sprintf(chkStr, "%s%s", str1, str2);

		/* Check Hash */
		int chainLen = findHash(h, chkStr);
		maxLen = chainLen > maxLen ? chainLen : maxLen;
		/* restore the char */
		str[i] = tmp;
	}

	return maxLen;
}

int compare(const void *a, const void *b)
{
	char *n1 = *(char **)a;
	char *n2 = *(char **)b;

	int len1 = strlen(n1);
	int len2 = strlen(n2);
	return (len1 - len2);
}

int longestStrChain(char ** words, int wordsSize)
{
	/* sort via "string length" */
	qsort(words, wordsSize, sizeof(char *), compare);
	/* Create hash table */
	HASH *h = createHash(MAX_WORDS_LEN);
	int ret = 0;
	for (int i = 0; i < wordsSize; i++)
	{
		// Get the previous max chain length based on current words[]
		int chkChain = getMaxPredecessorLen(h, words[i]) + 1;
		// Add current words[] to hash
		addHash(h, words[i], chkChain);       
		ret = chkChain > ret ? chkChain : ret;
	}
	releaseHash(h);
	return ret;
}

