
typedef struct __trieInfo {
    char used;
    struct __trieInfo *child[26];
} TRIE;

typedef struct {
    TRIE *t;
} WordDictionary;

static void word_dict_node_release(TRIE *t)
{
    if (!t)
        return;

    for (int i = 0; i < 26; i++)
        word_dict_node_release(t->child[i]);
    free(t);
}

static bool word_dict_search(TRIE *root, char *word)
{
    char *cur = word;
    while (*cur) {
        if (*cur == '.') {
            cur++;
            for (int x = 0; x < 26; x++) {
                if (root->child[x] && word_dict_search(root->child[x], cur))
                    return true;
            }
            return false;
        }

        int idx = *cur - 'a';
        if (!root->child[idx])
            return false;
        root = root->child[idx];
        cur++;
    }

    return root->used ? true : false;
}

/** Initialize your data structure here. */

WordDictionary *wordDictionaryCreate()
{
    WordDictionary *obj = malloc(sizeof(WordDictionary));
    obj->t = calloc(1, sizeof(TRIE));
    return obj;
}

/** Adds a word into the data structure. */
void wordDictionaryAddWord(WordDictionary *obj, char *word)
{
    TRIE *root = obj->t;
    char *cur = word;
    while (*cur) {
        int idx = *cur - 'a';
        if (!root->child[idx])
            root->child[idx] = calloc(1, sizeof(TRIE));
        root = root->child[idx];
        cur++;
    }

    root->used = 1;
}

/** Returns if the word is in the data structure. A word could contain the dot
 * character '.' to represent any one letter. */
bool wordDictionarySearch(WordDictionary *obj, char *word)
{
    return word_dict_search(obj->t, word);
}

void wordDictionaryFree(WordDictionary *obj)
{
    word_dict_node_release(obj->t);
    free(obj);
}

/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);

 * bool param_2 = wordDictionarySearch(obj, word);

 * wordDictionaryFree(obj);
 */
