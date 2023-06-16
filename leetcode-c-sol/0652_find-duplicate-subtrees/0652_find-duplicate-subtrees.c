enum
{
	SUCCESS = 0,
	FAILED,
	IGNORE,
};

typedef struct TreeNode NODE;

typedef struct hashT
{
	int size;
	int mod;
	int *done;
	char **arr;
}HASH;

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
	obj->done = calloc(size, sizeof(char *));
	obj->arr = calloc(size, sizeof(char *));
	return obj;
}

void addHash(HASH *ht, char *key) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index] != NULL)
	{
		index++;
		index %= ht->size;
	}

	ht->arr[index]= key;
}

int findHash(HASH *ht, char *key) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index] != NULL) 
	{
		if (!strcmp(ht->arr[index], key))
		{
			// We have updated this subtree
			if (ht->done[index])
			{
				return IGNORE;
			}
			ht->done[index] = 1;
			return SUCCESS;
		}
		index++;
		index %= ht->size;
	}
	return FAILED;
}

void releaseHash(HASH *ht)
{
	free(ht->done);
	free(ht->arr);
	free(ht);
}


char* dupSubtreeHelper(HASH *h, NODE *root, NODE ***ret, int *returnSize, int maxSize, char **strArr, int *strCtr)
{
	if (root == NULL)
	{
		char *retNull = calloc(2, sizeof(char));
		sprintf(retNull, "#");        
		strArr[*strCtr] = retNull;
		*strCtr += 1;
		return retNull;
	}

	// Recursive subtree
	char *retLeft = dupSubtreeHelper(h, root->left, ret, returnSize, maxSize, strArr, strCtr);
	char *retRight = dupSubtreeHelper(h, root->right, ret, returnSize, maxSize, strArr, strCtr);
	// Update the current local serialize string
	// Must free it after dupSubtreeHelper()
	char *localStr = calloc(maxSize, sizeof(char));
	sprintf(localStr, "%d-%s-%s", root->val, retLeft, retRight);
	strArr[*strCtr] = localStr;
	*strCtr += 1;

	// Hash Check
	int findRet = findHash(h, localStr);
	if (SUCCESS == findRet)
	{
		*ret = realloc(*ret, sizeof(NODE **)*(*returnSize + 1));
		(*ret)[*returnSize] = root;
		*returnSize += 1;
	} else if (FAILED == findRet)
	{
		addHash(h, localStr);
	}
	return localStr;
}

int countNodes(NODE *root)
{
	if (!root)
	{
		return 1;
	}    
	return countNodes(root->left) + countNodes(root->right) + 1;
}

struct TreeNode** findDuplicateSubtrees(struct TreeNode* root, int* returnSize)
{
	// Calculate totalNodes to make sure the size of dynamic allocate
	int totalNodes = countNodes(root);

	HASH *h = createHash(totalNodes);
	NODE **ret = malloc(sizeof(NODE *));
	*returnSize = 0;

	// prepare this to record all local serialize string in each subtree
	char **serializeNodesStr = malloc(sizeof(char *)*totalNodes);
	int serializeNodesCtr = 0;    
	dupSubtreeHelper(h, root, &ret, returnSize, totalNodes*13 /* maxSize => "[-2147483648]" */, 
			serializeNodesStr, &serializeNodesCtr);

	for (int i = 0; i < totalNodes; i++)
	{
		free(serializeNodesStr[i]);
	}
	free(serializeNodesStr);
	releaseHash(h);
	return ret;
}

