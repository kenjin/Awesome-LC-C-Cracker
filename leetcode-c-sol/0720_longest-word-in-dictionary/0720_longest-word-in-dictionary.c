typedef struct trieNode
{
	int found;
	struct trieNode *child[26];
} TRIE;

void freeTrie(TRIE *head)
{
	if (head == NULL)
	{
		return;
	}

	for (int i = 0; i < 26; i++)
	{
		freeTrie(head->child[i]);
	}
}

int addTrie(TRIE *node, char *name, int targetLen)
{
	TRIE *root = node;
	int ctr = 1;
	while (*name)
	{
		int idx = *name - 'a';
		if (NULL == root->child[idx])
		{
			root->child[idx] = calloc(1, sizeof(TRIE));
		}
		root = root->child[idx];
		if (!root->found)
		{
			break;
		}

		name++;
		ctr++;
	}

	if (ctr == targetLen)
	{
		root->found = 1;
	}
	return ctr;
}

int compare(const void *a, const void *b)
{
	char *s1 = *(char **)a;
	char *s2 = *(char **)b;    
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	if (strlen(s1) == strlen(s2))
	{
		return strcmp(s1, s2);
	}
	return len1 - len2;
}

char* longestWord(char ** words, int wordsSize)
{

	qsort(words, wordsSize, sizeof(char *), compare);

	struct trieNode *t = calloc(1, sizeof(TRIE));
	t->found = 1;
	int cur = 0, max = -1, retId = 0;
	for (int i = 0; i < wordsSize; i++)
	{
		int len = strlen(words[i]);
		if (cur+1 != len && cur != len)
		{
			break;            
		}
		cur = len;                 
		int tmp = addTrie(t, words[i], len);
		if (tmp == cur && tmp > max)
		{
			retId = i;
			max = tmp;
		}
	}

	freeTrie(t);
	return words[retId];    
}


