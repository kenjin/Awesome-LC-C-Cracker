#define LETTERS_NUM 26

typedef struct trieNode 
{
	char isEnd;
	struct trieNode  *charNode[LETTERS_NUM];
} Trie;

/** Initialize your data structure here. */

Trie* trieCreate()
{
	Trie *newNode = calloc(1, sizeof(Trie));
	return newNode;
}

/** Inserts a word into the trie. */
void trieInsert(Trie* head, char * word) 
{
	while (*word)
	{
		if (head->charNode[*word -'a'] == NULL)
		{
			head->charNode[*word -'a'] = trieCreate();
		}

		head = head->charNode[*word -'a'];        
		word++;
	}    

	head->isEnd = 1;
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* head, char * word) 
{
	if (head == NULL)  
	{
		return false;
	}

	while (*word)
	{
		head = head->charNode[*word - 'a'];        
		if (head == NULL)
		{
			return false;
		}
		word++;
	}
	return (head->isEnd ? true : false);
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* head, char * prefix) 
{
	if (head == NULL)  
	{
		return false;
	}

	while (*prefix)
	{
		head = head->charNode[*prefix - 'a'];        
		if (head == NULL)
		{
			return false;
		}
		prefix++;
	}
	return true;
}

void trieFree(Trie* head) 
{
	if (head == NULL)
	{
		return;
	}

	for (int i = 0; i < LETTERS_NUM; i++)
	{
		trieFree(head->charNode[i]);
	}
	free(head);
}

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);

 * bool param_2 = trieSearch(obj, word);

 * bool param_3 = trieStartsWith(obj, prefix);

 * trieFree(obj);
 */
