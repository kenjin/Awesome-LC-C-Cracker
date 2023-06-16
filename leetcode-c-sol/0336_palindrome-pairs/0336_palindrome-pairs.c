#define MAX_RET_SIZE(a) (a*(a-1))

typedef struct trieNode 
{
	int idx;
	struct trieNode *child[26];
} TRIE;

void freeTrie(TRIE *root)
{
	if (NULL == root)
	{
		return;
	}
	for (int i = 0; i < 26; i++)
	{
		freeTrie(root->child[i]);
	}

	free(root);
}

TRIE* createTrie()
{
	TRIE *obj = calloc(1, sizeof(TRIE));
	obj->idx = -1; 

	return obj;
}

void reverseStr(char *s)
{
	int head = 0;
	int tail = strlen(s) - 1;
	while (head < tail)
	{
		char tmp = s[head];
		s[head] = s[tail];
		s[tail] = tmp;
		head++;
		tail--;
	}
}

bool validPalindrome(char *s)
{
	int head = 0;
	int tail = strlen(s)-1;
	while (head < tail)
	{
		if (s[head] != s[tail])
		{
			return false;
		}
		head++;
		tail--;
	}

	return true;
}

void addTrie(TRIE *head, char *word, int index)
{
	char *tmpWord = word;
	while (*tmpWord)
	{
		int childIdx = *tmpWord - 'a';
		if (NULL == head->child[childIdx])
		{
			head->child[childIdx] = createTrie();
		}
		head = head->child[childIdx];
		tmpWord++;
	}

	head->idx = index;
}

int findTrie(TRIE *head, char *word)
{
	int len = strlen(word);
	char *rword = calloc(len+1, sizeof(char));
	strcpy(rword, word);
	reverseStr(rword);

	char *tmpWord = rword;
	while (*tmpWord)
	{
		int childIdx = *tmpWord - 'a';
		if (NULL == head->child[childIdx])
		{
			free(rword);
			return -1;
		}
		head = head->child[childIdx];
		tmpWord++;
	}

	free(rword);
	return head->idx;
}

void updateResult(int **ret, int **returnColumnSizes, int *retCtr, int idx1, int idx2)
{
	ret[*retCtr] = malloc(sizeof(int)*2);
	ret[*retCtr][0] = idx1;
	ret[*retCtr][1] = idx2;
	(*returnColumnSizes)[*retCtr] = 2;
	*retCtr += 1;
}

int** palindromePairs(char ** words, int wordsSize, int* returnSize, int** returnColumnSizes)
{
	int **ret = malloc(sizeof(int *)*MAX_RET_SIZE(wordsSize));
	*returnColumnSizes = malloc(sizeof(int)*MAX_RET_SIZE(wordsSize));
	*returnSize = 0;

	TRIE *t = createTrie();
	int emptyIdx = -1;
	for (int i = 0; i < wordsSize; i++)
	{
		if (strlen(words[i]) == 0)
		{
			emptyIdx = i;
			continue;
		}
		addTrie(t, words[i], i);        
	}

	for (int i = 0; i < wordsSize; i++)
	{        
		int curLen = strlen(words[i]);        
		if (curLen == 0)
		{
			continue;
		}
		// Current word is palindrome and there is an empty string in words
		if (validPalindrome(words[i]) && emptyIdx != -1)
		{
			updateResult(ret, returnColumnSizes, returnSize, i, emptyIdx);
			updateResult(ret, returnColumnSizes, returnSize, emptyIdx, i);
		}

		// Check that the current reverse word has existed in TRIE
		int findIdx = findTrie(t, words[i]);
		if (-1 != findIdx && findIdx != i)
		{
			updateResult(ret, returnColumnSizes, returnSize, i, findIdx);
		}

		// Split the current word to left half and right half
		char *lStr = calloc(curLen+1, sizeof(char));
		strcpy(lStr, words[i]);
		char *rStr = NULL;
		for (int x = 1; x < curLen; x++)
		{
			lStr[x] = '\0';
			rStr = &(words[i][x]);
			// Left is palindrome, check right in TRIE
			if (validPalindrome(lStr))
			{
				int findIdx_right = findTrie(t, rStr);
				if (-1 != findIdx_right)
				{
					updateResult(ret, returnColumnSizes, returnSize, findIdx_right, i);
				}
			}

			// Right is palindrome, check left in TRIE
			if (validPalindrome(rStr))
			{
				int findIdx_left = findTrie(t, lStr);
				if (-1 != findIdx_left)
				{
					updateResult(ret, returnColumnSizes, returnSize, i, findIdx_left);
				}
			}                        

			lStr[x] = words[i][x];
		}
		free(lStr);
	}

	freeTrie(t);
	return ret;
}

