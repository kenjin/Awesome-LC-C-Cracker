
typedef struct __trie {
	struct __trie *chd[26];
	char is_set;
} Trie;

/** Initialize your data structure here. */

Trie* trieCreate() {
	Trie *obj = calloc(1, sizeof(Trie));
	return obj;
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, char * word)
{
	Trie *root = obj;
	while (*word) {
		char cur = *word - 'a';
		if (NULL == root->chd[cur]) {
			root->chd[cur] = trieCreate();
		}
		root = root->chd[cur];
		word++;
	}
	root->is_set = 1;
}

/* Return NULL pointer if can't find prefix string, otherwise return prefix leaf node */
static inline Trie* trie_get_prefix_leaf(Trie* obj, char * prefix)
{
	Trie *root = obj;
	while (*prefix) {
		root = root->chd[*prefix - 'a'];
		if (!root)
			return NULL;
		prefix++;
	}
	return root;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, char * prefix)
{
	Trie *leaf = trie_get_prefix_leaf(obj, prefix);
	return leaf ? true : false;
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, char * word)
{
	Trie *leaf = trie_get_prefix_leaf(obj, word);
	return (leaf && leaf->is_set) ? true : false;
}

void trieFree(Trie* obj)
{
	if (!obj)
		return;

	for (int i = 0; i < 26; i++)
		trieFree(obj->chd[i]);
	free(obj);
}

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);

 * bool param_2 = trieSearch(obj, word);

 * bool param_3 = trieStartsWith(obj, prefix);

 * trieFree(obj);
 */
