typedef struct hashList HASH_LIST;
struct hashList 
{
	int len;
	int groupIdx;
	char *str;
	HASH_LIST *next;
};

typedef struct 
{
	int size;
	int mod;
	HASH_LIST **list
} HASH;

/** Initialize your data structure here. */

HASH_LIST* createNewNode()
{
	HASH_LIST *newNode = calloc(1, sizeof(HASH_LIST));
	newNode->len = -1;
	newNode->next = NULL;	
	return newNode;
}

HASH* hashCreate(int size) 
{
	HASH *hash = malloc(sizeof(HASH));
	hash->size = hash->mod = size;
	hash->list = malloc(sizeof(HASH_LIST*)*size);
	for (int i = 0; i < size; i++)
	{
		/* Pre-create one node for each bucket */
		hash->list[i] = createNewNode();
	}	
	return hash;
}

int doHash(int mod, char *s, int len)
{
	int diff = s[0] - 'a';
	if (len == 1)
	{
		return s[0] % mod;
	} else if (len == 2)
	{
		return (s[0] + s[1]) % mod;
	} else
	{
		return (s[0] + s[1] + s[2]) % mod;
	}
}

void remapString(char *dst, char *src, int len)
{
	// remap the first char to 'a': "bd" -> 'b'-1 'd'-1 -> "ac"
	int diff = src[0] - 'a';
	for (int x = 0; x < len; x++)
	{
		dst[x] = src[x] - diff;
		if (dst[x] < 'a')
		{
			dst[x] += 26;
		}
	}
}

/** value will always be non-negative. */
void hashInsert(HASH* obj, char *str, int groupIdx)
{
	int len = strlen(str);
	char *newStr = calloc(len+1, sizeof(char));
	remapString(newStr, str, len);

	int hashIndex = doHash(obj->mod, newStr, len);
	HASH_LIST *newNode = createNewNode(); /* Create node */
	if (obj->list[hashIndex]->next == NULL) /* Bucket is empty, first time put */
	{
		obj->list[hashIndex]->len = len;
		obj->list[hashIndex]->groupIdx = groupIdx;
		obj->list[hashIndex]->str = newStr;
		obj->list[hashIndex]->next = newNode;
	} else /* Bucket is not empty*/
	{   
		HASH_LIST *tmp = obj->list[hashIndex];
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->len = len;
		tmp->groupIdx = groupIdx;
		tmp->str = newStr;
		tmp->next = newNode;
	}
}

int hashFind(HASH* obj, char *str) 
{
	int len = strlen(str);
	char *reduceStr = calloc(len+1, sizeof(char));
	remapString(reduceStr, str, len);

	int hashIndex = doHash(obj->mod, reduceStr, len);
	HASH_LIST *tmp = obj->list[hashIndex];
	// check first list
	if (tmp->len == len && !strcmp(tmp->str, reduceStr))
	{
		free(reduceStr);
		return tmp->groupIdx;
	}
	// check the second to the end, the purpose is to cound the last node
	// if the input key/target is -1/XX, it will match to the last node (because default key is -1)
	while (tmp->next != NULL)
	{
		if (tmp->len == len && !strcmp(tmp->str, reduceStr))
		{
			free(reduceStr);
			return tmp->groupIdx;
		}
		tmp = tmp->next;                
	}

	// printf(" Not found %s\n", str);
	free(reduceStr);
	return -1;
}

void hashFree(HASH* obj) 
{
	for (int i = 0; i < obj->size; i++)
	{
		HASH_LIST *tmp = obj->list[i];
		while (tmp)
		{
			HASH_LIST *delNode = tmp;
			tmp = tmp->next;
			free(delNode->str);
			free(delNode);
		}   
	}
	free(obj);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** groupStrings(char ** strings, int stringsSize, int* returnSize, int** returnColumnSizes)
{
	HASH *h = hashCreate(76);
	char ***ret = malloc(sizeof(char **));
	*returnSize = 0;
	*returnColumnSizes = calloc(1, sizeof(int));
	for (int i = 0; i < stringsSize; i++)
	{
		int group = hashFind(h, strings[i]);
		if (-1 == group)
		{
			// Create new group
			*returnSize += 1;            
			ret = realloc(ret, sizeof(char **)*(*returnSize));
			*returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*(*returnSize));
			// Add first col member to new group
			int curGroup = (*returnSize) - 1;
			(*returnColumnSizes)[curGroup] = 1;
			ret[curGroup] = malloc(sizeof(char *));
			ret[curGroup][0] = calloc(strlen(strings[i])+1, sizeof(char));
			strcpy(ret[curGroup][0], strings[i]);
			// Insert to hash table
			hashInsert(h, strings[i], curGroup);
		} else
		{
			// Add new col member to group
			(*returnColumnSizes)[group] += 1;
			ret[group] = realloc(ret[group], sizeof(char *)*((*returnColumnSizes)[group]));
			ret[group][ (*returnColumnSizes)[group] -1 ] = calloc(strlen(strings[i])+1, sizeof(char));
			strcpy(ret[group][ (*returnColumnSizes)[group] -1 ], strings[i]);
		}
	}
	return ret;
}
