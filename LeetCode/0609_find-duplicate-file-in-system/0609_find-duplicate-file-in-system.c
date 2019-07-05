#define HASH_SIZE           10000
#define MALLOC_SIZE_UNIT    20000

typedef struct bucketNodeInfo  NODE;
struct bucketNodeInfo 
{
	char content[51];
	int len;
	int retIdx;
	NODE *next;
};

// Hash Table
typedef struct 
{	
	int size;
	NODE *bucket[HASH_SIZE];    
} HASH;

NODE* createNewNode()
{
	NODE *newNode = calloc(1, sizeof(NODE));
	newNode->retIdx = -1;		
	return newNode;
}

HASH* createHash(int size) 
{
	HASH *obj = malloc(sizeof(HASH));
	obj->size = size;
	for (int i = 0; i < size; i++)
	{
		/* Pre-create one node for each bucket */
		obj->bucket[i] = createNewNode();
	}	
	return obj;
}

void freeHash(HASH* obj) 
{
	for (int i = 0; i < obj->size; i++)
	{
		NODE *tmp = obj->bucket[i];
		while (tmp)
		{
			NODE *delNode = tmp;
			tmp = tmp->next;
			free(delNode);
		}   
	}
	free(obj);
}

int hash(HASH *obj, char *str, int keyLen)
{
	size_t hash = 5381;
	while (*str)
	{
		hash = 33 * hash ^ (unsigned char) *str++;
	}
	return hash % obj->size;
}

/* Hash add */
void addHash(HASH* obj, char *content, int idx)
{
	int len = strlen(content);
	int hashIndex = hash(obj, content, len);
	/* Create bucket node for hash */
	NODE *newNode = createNewNode();

	if (obj->bucket[hashIndex]->next == NULL) /* Bucket is empty, first time put */
	{
		strcpy(obj->bucket[hashIndex]->content, content);
		obj->bucket[hashIndex]->len = len;
		obj->bucket[hashIndex]->retIdx = idx;
		obj->bucket[hashIndex]->next = newNode;
	} else /* Bucket is not empty*/
	{        
		NODE *tmp = obj->bucket[hashIndex];
		while (tmp->next != NULL)
		{
			if (tmp->len == len && !strcmp(tmp->content, content)) /* duplicate content */
			{				
				free(newNode);
				return;
			}
			tmp = tmp->next;
		}        
		strcpy(tmp->content, content);
		tmp->len = len;
		tmp->retIdx = idx;
		tmp->next = newNode;
	}
}

/* Hash find */
int findHash(HASH* obj, char *content)
{    
	int len = strlen(content);
	int hashIndex = hash(obj, content, len);

	NODE *tmp = obj->bucket[hashIndex];
	while (tmp != NULL)
	{
		if (tmp->len == len && !strcmp(tmp->content, content))
		{
			return tmp->retIdx;       
		}
		tmp = tmp->next;
	}
	return -1;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** findDuplicate(char ** paths, int pathsSize, int* returnSize, int** returnColumnSizes)
{
	HASH *h = createHash(HASH_SIZE);
	char ***ret = malloc(sizeof(char**)*MALLOC_SIZE_UNIT);
	for (int x = 0; x < MALLOC_SIZE_UNIT; x++)
	{
		ret[x] = malloc(sizeof(char *));        
	}
	*returnColumnSizes = calloc(MALLOC_SIZE_UNIT, sizeof(int));
	*returnSize = 0;
	for (int i = 0; i < pathsSize; i++)
	{
		int maxLen = strlen(paths[i]);
		char *dName = calloc(maxLen, sizeof(char));
		char *fName = calloc(maxLen, sizeof(char));
		char content[51] = {0};
		int idx = 0;
		// Get directory name
		while (paths[i][idx] != ' ')
		{
			dName[idx] = paths[i][idx];
			idx++;
		}

		while (paths[i][idx] != '\0')
		{
			while (paths[i][idx] == ' ')
			{
				idx++; 
			}
			// assume the directory name, file name and file content only has letters and digits
			int fIdx = 0;
			memset(fName, 0, sizeof(char)*maxLen);
			memset(content, 0, sizeof(content));
			while (paths[i][idx] != '.')
			{
				fName[fIdx] = paths[i][idx];
				fIdx++;
				idx++;
			}
			// copy ".txt" string
			strcpy(&(fName[fIdx]), ".txt");
			idx += 5; // "txt("
			int cIdx = 0;
			while (paths[i][idx] != ')')
			{
				content[cIdx] = paths[i][idx];
				cIdx++;
				idx++;
			}
			idx++; // skip ')'

			int retIdx = findHash(h, content);
			if (-1 == retIdx)
			{
				addHash(h, content, *returnSize);
				int groupIdx = (*returnColumnSizes)[*returnSize];
				ret[*returnSize] = realloc(ret[*returnSize], sizeof(char *)*(groupIdx+1));
				ret[*returnSize][groupIdx] = calloc(maxLen, sizeof(char));
				sprintf(ret[*returnSize][groupIdx], "%s/%s", dName, fName);      
				(*returnColumnSizes)[*returnSize] += 1;
				*returnSize += 1;
			} else
			{
				int groupIdx = (*returnColumnSizes)[retIdx];
				ret[retIdx] = realloc(ret[retIdx], sizeof(char *)*(groupIdx+1));
				ret[retIdx][groupIdx] = calloc(maxLen, sizeof(char));
				sprintf(ret[retIdx][groupIdx], "%s/%s", dName, fName);
				(*returnColumnSizes)[retIdx] += 1;
			}
		}
		free(dName);
		free(fName);
	}

	// Remove the signle one
	char ***ans = malloc(sizeof(char ***)*(*returnSize));
	int totalTmp = *returnSize;
	*returnSize = 0;
	for (int i = 0; i < totalTmp; i++)
	{
		int memberCtr = (*returnColumnSizes)[i];
		if (memberCtr == 1)
		{
			free(ret[i][0]);
		} else
		{
			ans[*returnSize] = malloc(sizeof(char*)*memberCtr);
			for (int x = 0; x < memberCtr; x++)
			{
				int len = strlen(ret[i][x]);
				ans[*returnSize][x] = calloc(len+1, sizeof(char));
				strcpy(ans[*returnSize][x], ret[i][x]);
				free(ret[i][x]);
			}
			(*returnColumnSizes)[*returnSize] = memberCtr;
			*returnSize += 1;
		}
		free(ret[i]);
	}

	free(ret);
	free(h);
	return ans;
}

