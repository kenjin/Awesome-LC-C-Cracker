typedef struct trieNode
{
	int used;
	struct trieNode *chd[27];
} TRIE;

void freeTrie(TRIE *t)
{
	for (int i = 0; i < 27; i++)
	{
		if (t->chd[i])
		{
			freeTrie(t->chd[i]);
		}
	}    
	free(t);
}

int addTrie(TRIE *t, char *s)
{
	int len = 0;
	TRIE *root = t;
	while (*s)
	{
		int idx = (*s == '/' ? 26 : *s-'a');              
		if (NULL == root->chd[idx])
		{
			root->chd[idx] = calloc(1, sizeof(TRIE));
		}
		root = root->chd[idx];
		if (root->used && *(s+1) == '/')
		{
			return -1;
		}
		len++;
		s++;
	}    
	root->used = 1;
	return len;
}

int compare(const void *a, const void *b)
{
	char *s1 = *(char **)a;
	char *s2 = *(char **)b;    
	return strlen(s1) - strlen(s2);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** removeSubfolders(char ** folder, int folderSize, int* returnSize)
{
	qsort(folder, folderSize, sizeof(char *), compare);

	int len;
	*returnSize = 0;
	char **ret = malloc(sizeof(char *)*folderSize);
	TRIE *t = calloc(1, sizeof(TRIE));
	for (int i = 0; i < folderSize; i++)
	{
		if (-1 != (len = addTrie(t, folder[i])))
		{
			ret[*returnSize] = calloc(len+1, sizeof(char));
			strcpy(ret[*returnSize], folder[i]);
			*returnSize += 1;
		}
	}

	freeTrie(t);
	return ret;
}


