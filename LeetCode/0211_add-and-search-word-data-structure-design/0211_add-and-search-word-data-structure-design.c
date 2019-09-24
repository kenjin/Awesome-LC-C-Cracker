
typedef struct trieInfo
{
	char add;
	struct trieInfo *child[26];
} TRIE;

typedef struct 
{
	TRIE *t;
} WordDictionary;

/** Initialize your data structure here. */

WordDictionary* wordDictionaryCreate() 
{
	WordDictionary *obj = malloc(sizeof(WordDictionary));
	obj->t = calloc(1, sizeof(TRIE));

	return obj;
}

/** Adds a word into the data structure. */
void wordDictionaryAddWord(WordDictionary* obj, char * word) 
{       
	TRIE *root = obj->t;
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

	root->add = 1;
}

bool wordDictionarySearchHeper(TRIE *root, char * word) 
{
	char *tmpWord = word;
	while (*tmpWord)
	{
		if (*tmpWord == '.')
		{
			tmpWord++;
			for (int x = 0; x < 26; x++)
			{
				if (root->child[x] != NULL && wordDictionarySearchHeper(root->child[x], tmpWord))
				{
					return true;
				}                
			}
			return false;
		}

		int idx = *tmpWord - 'a';
		if (root->child[idx] == NULL)
		{
			return false;
		}
		root = root->child[idx];
		tmpWord++;
	}

	return root->add ? true : false;
}

/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
bool wordDictionarySearch(WordDictionary* obj, char * word) 
{
	return wordDictionarySearchHeper(obj->t, word);
}

void wordDictionaryFreeHelper(TRIE *t)
{
	if (NULL == t)
	{
		return;
	}
	for (int i = 0; i < 26; i++)
	{
		wordDictionaryFreeHelper(t->child[i]);
	}

	free(t);
}

void wordDictionaryFree(WordDictionary* obj) 
{
	wordDictionaryFreeHelper(obj->t);
	free(obj);
}

/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);

 * bool param_2 = wordDictionarySearch(obj, word);

 * wordDictionaryFree(obj);
 */
