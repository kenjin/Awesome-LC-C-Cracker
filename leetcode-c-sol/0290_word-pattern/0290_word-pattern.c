typedef struct
{
	int used;
	char *s;
} WORD;

typedef struct
{
	int mod;
	char *arr[27];
} HASH;

int hash(HASH *obj, char *str)
{
	size_t hash = 5381;
	while (*str)
	{
		hash = 33 * hash ^ (unsigned char) *str++;
	}
	return hash % obj->mod;
}

HASH* createHash()
{
	HASH *obj = malloc(sizeof(HASH));
	obj->mod = 27;
	for (int x = 0; x < 27; x++)
	{
		obj->arr[x] = NULL;
	}
	return obj;
}

void addHash(HASH *ht, char *key)
{
	int keyLen = strlen(key);
	int index = hash(ht, key);
	while (ht->arr[index] != NULL)
	{
		index++;
		index %= 27;
	}

	ht->arr[index] = calloc(keyLen+1, sizeof(int));
	strcpy(ht->arr[index], key);
}

int findHash(HASH *ht, char *key) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key);    
	while (ht->arr[index] != NULL) 
	{
		if (!strcmp(ht->arr[index], key))
		{
			return 1;
		}
		index++;
		index %= 27;
	}
	return 0;
}

void releaseHash(HASH *ht)
{
	for (int i = 0; i < 27; i++)
	{
		free(ht->arr[i]);
	}
	free(ht);
}

bool wordPattern(char * pattern, char * str)
{
	WORD w[26] = {0};

	HASH *h = createHash();
	bool ret = false;
	char *delim = " ";
	char *pch;
	pch = strtok(str, delim);
	while (pch != NULL)
	{
		if (*pattern == 0)
		{
			break;
		}

		int curPatternIdx = *pattern - 'a';
		if (!w[curPatternIdx].used)
		{
			if (findHash(h, pch))
			{
				break;
			}
			int len = strlen(pch);
			w[curPatternIdx].s = calloc(len+1, sizeof(char));
			strcpy(w[curPatternIdx].s, pch);
			w[curPatternIdx].used = 1;
			addHash(h, pch);
		} else
		{
			if (strcmp(w[curPatternIdx].s, pch) != 0)
			{
				break;
			}
		}

		pattern++;
		pch = strtok (NULL, delim);
	}

	if (*pattern == 0 && pch == NULL)
	{
		ret = true;
	}

	for (int i = 0; i < 26; i++)
	{
		free(w[i].s);
	}
	releaseHash(h);

	return ret;
}


