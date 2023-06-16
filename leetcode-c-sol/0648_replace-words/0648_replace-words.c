#define ROOT_SIZE 1001

typedef struct trieNode
{
	int len;
	char str[ROOT_SIZE];
	struct trieNode *child[26];
} TRIE;

void freeTrie(TRIE *root)
{
	if (root == NULL)
	{
		return ;
	}

	for (int i = 0; i < 26; i++)
	{
		freeTrie(root->child[i]);
	}
	free(root);
}

// Return the input word if we can not find the string from trie
char* findTrie(TRIE *root, char *word)
{
	char *tmpWord = word;
	while (*tmpWord)
	{
		int idx = *tmpWord - 'a';
		if (root->child[idx] == NULL || root->len != 0)
		{
			break;
		}
		root = root->child[idx];
		tmpWord++;
	}

	return (root->len != 0 ? root->str : word);
}

void addTrie(TRIE *root, char *word)
{
	char *tmpWord = word;
	while (*tmpWord)
	{
		int idx = *tmpWord - 'a';
		if (root->child[idx] == NULL)
		{
			root->child[idx] = calloc(1, sizeof(TRIE));            
		}
		root = root->child[idx];
		tmpWord++;
	}

	root->len = strlen(word);
	strcpy(root->str, word);
}

void sentenceParser(TRIE *node, char *sentence)
{
	char *delim = " ", *pch = NULL, *findRet = NULL;
	int len = strlen(sentence);

	char *tmp = calloc(len+1, sizeof(char));
	strcpy(tmp, sentence);
	memset(sentence, 0, sizeof(char)*len);        

	// First token, ignore space char
	pch = strtok(tmp, delim);
	findRet = findTrie(node, pch);
	strcat(sentence, findRet);
	// Check the rest token
	pch = strtok(NULL, delim);      
	while (pch != NULL)
	{
		strcat(sentence, " ");        
		findRet = findTrie(node, pch);
		strcat(sentence, findRet);
		pch = strtok (NULL, delim);        
	}
	free(tmp);
}

char* replaceWords(char ** dict, int dictSize, char * sentence)
{
	TRIE *head = calloc(1, sizeof(TRIE));

	// Add root
	for (int i = 0; i < dictSize; i++)
	{
		if (dict[i] == findTrie(head, dict[i]))
		{
			addTrie(head, dict[i]);
		}
	}

	sentenceParser(head, sentence);
	freeTrie(head);
	return sentence;
}


