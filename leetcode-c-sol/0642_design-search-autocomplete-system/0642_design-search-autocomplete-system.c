#define SENTENCE_SIZE       101
#define ALPHA_SPACE_SIZE    27
#define ALPHABET_SIZE       26
#define HOT_TOP_SIZE        3

typedef struct dataRetInfo
{
	char str[SENTENCE_SIZE];
	int times;
} DATA;

typedef struct trieInfo
{
	DATA data;
	struct trieInfo *charNode[ALPHA_SPACE_SIZE];
} TRIE;

typedef struct
{
	TRIE *root;
	char *input;
	int inputLen;
	char inputFail;
} AutocompleteSystem;


TRIE* createTrieNode()
{
	TRIE *newOne = calloc(1, sizeof(TRIE));
	return newOne;
}

void insertTrie(AutocompleteSystem *obj, char *word, int times)
{
	TRIE *head = obj->root;
	char *tmp = word;
	while (*tmp)
	{
		int idx = (*tmp == ' ' ? ALPHABET_SIZE : (*tmp - 'a'));
		if (NULL == head->charNode[idx])
		{            
			head->charNode[idx] = createTrieNode();
		}
		head = head->charNode[idx];
		tmp++;
	}

	head->data.times += times;
	strcpy(head->data.str, word);
}

void cmpAndSwap(DATA *a, DATA *b)
{
	DATA tmp;
	if (a->times <= b->times)
	{
		if (a->times == b->times &&            
				strcmp(a->str, b->str) <= 0) // smaller one appears first
		{
			return;
		}
		memcpy(&tmp, a, sizeof(DATA));
		memcpy(a, b, sizeof(DATA));
		memcpy(b, &tmp, sizeof(DATA));
	}
}

void findTrieHelper(TRIE *head, DATA *ret)
{
	for (int i = 0; i < ALPHA_SPACE_SIZE; i++)
	{
		if (head->charNode[i])
		{
			findTrieHelper(head->charNode[i], ret);
		}
	}

	if (head->data.times > 0)
	{
		DATA cur;
		memcpy(&cur, &(head->data), sizeof(DATA));  
		for (int x = 0; x < HOT_TOP_SIZE; x++)
		{
			cmpAndSwap(&(ret[x]), &cur);
		}   
	}
}

void freeTrie(TRIE *head)
{
	if (head == NULL)
	{
		return;
	}

	for (int i = 0; i < ALPHA_SPACE_SIZE; i++)
	{
		freeTrie(head->charNode[i]);
	}
}

AutocompleteSystem* autocompleteSystemCreate(char ** sentences, int sentencesSize, int* times, int timesSize) 
{
	AutocompleteSystem *obj = malloc(sizeof(AutocompleteSystem));
	obj->root = createTrieNode();
	obj->input = calloc(SENTENCE_SIZE, sizeof(char));
	obj->inputLen = 0;    
	obj->inputFail = 0;    

	for (int i = 0; i < sentencesSize; i++)
	{
		insertTrie(obj, sentences[i], times[i]);
	}

	return obj;
}

char ** autocompleteSystemInput(AutocompleteSystem* obj, char c, int* retSize) 
{
	char **ret = NULL;
	int retCtr = 0;
	// Check the "END char"
	if (c == '#')
	{
		// Add this typing string
		insertTrie(obj, obj->input, 1);
		// Reset Input        
		memset(obj->input, 0, sizeof(char)*101);
		obj->inputLen = 0;
		obj->inputFail = 0;
		goto out;
	}    

	// Update current character
	obj->input[obj->inputLen] = c;
	obj->inputLen += 1;

	// Input is fail, no need to waste time to find from trie
	if (obj->inputFail)
	{
		goto out;
	}

	// Find input from trie
	TRIE *head = obj->root;
	char *word = obj->input;
	int idx;
	while (*word)
	{
		idx = (*word == ' ' ? ALPHABET_SIZE : (*word - 'a'));
		if (NULL == head->charNode[idx])
		{
			obj->inputFail = 1;
			goto out;
		}
		head = head->charNode[idx];
		word++;
	}

	if (head)
	{        
		DATA result[HOT_TOP_SIZE] = {0};
		findTrieHelper(head, result);

		ret = malloc(sizeof(char *)*HOT_TOP_SIZE);
		for (int x = 0; x < HOT_TOP_SIZE; x++)
		{
			if (result[x].times == 0)
			{
				continue;
			}
			ret[retCtr] = calloc(SENTENCE_SIZE, sizeof(char));
			strcpy(ret[retCtr], result[x].str);
			retCtr += 1;
		}
	}

out:
	*retSize = retCtr;
	return ret;
}

void autocompleteSystemFree(AutocompleteSystem* obj) 
{    
	freeTrie(obj->root);
	free(obj->input);  
	free(obj);
}

/**
 * Your AutocompleteSystem struct will be instantiated and called as such:
 * AutocompleteSystem* obj = autocompleteSystemCreate(sentences, sentencesSize, times, timesSize);
 * char ** param_1 = autocompleteSystemInput(obj, c, retSize);

 * autocompleteSystemFree(obj);
 */
