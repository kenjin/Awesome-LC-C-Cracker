typedef struct trieNode TRIE;

struct trieNode
{
	int found;
	struct trieNode *child[26];
};

void addTrie(TRIE *node, char *name)
{
	TRIE *root = node;
	while (*name)
	{
		int idx = *name - 'a';
		root->child[idx] = calloc(1, sizeof(TRIE));
		root = root->child[idx];
		name++;
	}

	root->found = 1;
}

bool findTrie(TRIE *root, char *target)
{
	char prev = 0;
	while (*target)
	{
		int idx = *target - 'a';
		if (NULL == root->child[idx])
		{
			if (prev != 0 && *target == prev)
			{
				target++;
				continue;
			} else
			{
				return false;
			}
		}

		prev = *target;
		root = root->child[idx];
		target++;
	}

	return (root->found == 1);
}

bool isLongPressedName(char * name, char * typed)
{
	TRIE *root = calloc(1, sizeof(TRIE));
	addTrie(root, name);
	return findTrie(root, typed);
}
