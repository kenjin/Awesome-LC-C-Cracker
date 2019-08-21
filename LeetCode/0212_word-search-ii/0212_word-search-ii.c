typedef struct trieNode
{
	char *str;
	struct trieNode *child[26];
}TRIE;


TRIE* createNode(char c)
{
	TRIE *newNode = calloc(1, sizeof(TRIE));
	return newNode;
}

void freeTrie(TRIE *t)
{
	if (NULL == t)
	{
		return;
	}

	for (int i = 0; i < 26; i++)
	{
		freeTrie(t->child[i]);
	}
	free(t);
}

char findTrie(TRIE *t, char *s)
{
	TRIE *head = t;
	while (*s)
	{
		int idx = *s - 'a';
		if (head->child[idx] == NULL)
		{
			return 0;        
		}
		head = head->child[idx];
		s++;
	}
	return 1;
}

void updateTrie(TRIE *t, char *str)
{
	TRIE *head = t;
	char *s = str;
	while (*s)
	{
		int idx = *s - 'a';
		if (head->child[idx] == NULL)
		{
			head->child[idx] = createNode(*s);            
		}
		head = head->child[idx];
		s++;
	}

	head->str = str;
}

void DFS(TRIE *t, char** board, int rSize, int cSize, int curRow, int curCol, char **ret, int* returnSize)
{
	if (curRow == rSize || curCol == cSize || curRow < 0 || curCol < 0 ||  // Exceed Limit
			board[curRow][curCol] == -1 || // Has been visited
			t->child[board[curRow][curCol] - 'a'] == NULL) // This path is not in the words
	{
		return;
	}

	t = t->child[board[curRow][curCol] - 'a'];
	if (t->str != NULL)
	{        
		ret[*returnSize] = t->str;
		*returnSize += 1;
		t->str = NULL;
	}

	char dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	char tmp = board[curRow][curCol];
	board[curRow][curCol] = -1;
	for (int x = 0; x < 4; x++)
	{
		DFS(t, board, rSize, cSize, curRow + dir[x][0], curCol + dir[x][1], ret, returnSize);
	}
	board[curRow][curCol] = tmp;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** findWords(char** board, int boardSize, int* boardColSize, char ** words, int wordsSize, int* returnSize)
{
	TRIE *t = createNode(0);
	for (int i = 0; i < wordsSize; i++)
	{
		updateTrie(t, words[i]);
	}

	char **ret = malloc(sizeof(char *)*wordsSize);
	*returnSize = 0;
	for (int i = 0; i < boardSize; i++)
	{        
		for (int j = 0; j < boardColSize[0]; j++)
		{
			DFS(t, board, boardSize, boardColSize[0], i, j, ret, returnSize);
		}
	}

	freeTrie(t);
	return ret;    
}

