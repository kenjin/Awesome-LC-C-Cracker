typedef struct hashT HASH;

struct hashInfo
{
	char used;
	char str[11];     // 1 <= k <=10
};

struct hashT
{
	int size;
	int mod;
	struct hashInfo **arr;
};

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
	obj->mod = size;
	obj->arr = malloc(sizeof(struct hashInfo)*(size));
	for (int x = 0; x < size; x++)
	{
		struct hashInfo *newInfo = calloc(1, sizeof(struct hashInfo));
		obj->arr[x] = newInfo;
	}
	return obj;
}

void addHash(HASH *ht, char *key) 
{
	int index = hash(ht, key);
	while (ht->arr[index]->used) 
	{
		index++;
		index %= ht->size;
	}

	ht->arr[index]->used = 1;
	strcpy(ht->arr[index]->str, key);
}

void delHash(HASH *ht, char *key) 
{
	int index = hash(ht, key);
	while (ht->arr[index]->used) 
	{
		if (!strcmp(ht->arr[index]->str, key))
		{
			ht->arr[index]->used = 0;
			return;
		}
		index++;
		index %= ht->size;
	}
}

bool findHash(HASH *ht, char *key) 
{
	int index = hash(ht, key);
	while (ht->arr[index]->used) 
	{
		if (!strcmp(ht->arr[index]->str, key))
		{
			return true;
		}
		index++;
		index %= ht->size;
	}
	return false;
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

bool DFS(char *ret, char *pwd, HASH *h, int k, int n, int idx, int nodeCtr, int totalNode)
{
	if (nodeCtr == totalNode)
	{
		return true;
	}

	bool done = false;
	char *tmpPwd= calloc(n+1, sizeof(char));
	strcpy(tmpPwd, pwd);
	strcpy(pwd, &(tmpPwd[1]));
	for (int x = 0; x < k; x++)
	{
		pwd[n-1] = x + '0';
		if (!findHash(h, pwd))
		{
			addHash(h, pwd);
			strcpy(tmpPwd, pwd);
			if (DFS(ret, pwd, h, k, n, idx+1, nodeCtr+1, totalNode))
			{
				ret[idx] = x + '0';
				done = true;
				break;
			}
			// recover password
			delHash(h, tmpPwd);
			strcpy(pwd, tmpPwd);
		}
	}

	free(tmpPwd);
	return done;
}

char * crackSafe(int n, int k)
{
	int totalNode = pow(k, n);
	HASH *h = createHash(totalNode);

	char **node = malloc(sizeof(char *)*totalNode);
	for (int i = 0; i < totalNode; i++)
	{
		node[i] = calloc(n+1, sizeof(char));
	}

	// result len = k^n + (n-1)
	char *ret = calloc(totalNode+(n-1)+1, sizeof(char));    
	char *pwd = calloc(n+1, sizeof(char));
	for (int x = 0; x < n; x++)
	{
		pwd[x] = '0';
	}
	strcpy(ret, pwd);
	int idx = n-1;
	int ctr = 0;
	DFS(ret, pwd, h, k, n, idx, ctr, totalNode);

	free(pwd);
	releaseHash(h);
	return ret;
}

