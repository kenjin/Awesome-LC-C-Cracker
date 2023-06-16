
typedef struct __list_node {
    char c;
    struct __list_node *next;
} list_t;

typedef struct __trie {
    char used;
    struct __trie *child[26];
} trie_t;

typedef struct {
    list_t *lh;
    trie_t *t;
} StreamChecker;

/* insert string to trie from last char to first char */
static inline void trie_add_backward(trie_t *t, char *str)
{
    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--) {
        /* Words will only consist of lowercase English letters */
        int idx = str[i] - 'a';
        if (NULL == t->child[idx])
            t->child[idx] = calloc(1, sizeof(trie_t));

        t = t->child[idx];
    }
    t->used = 1;
}

static inline bool trie_check(trie_t *t, list_t *root)
{
    while (root) {
        int idx = root->c - 'a';
        if (t->used)
            return true;
        if (NULL == t->child[idx])
            return false;

        t = t->child[idx];
        root = root->next;
    }
    return (t->used);
}

static inline void trie_release(trie_t *t)
{
    if (!t)
        return;
    for (int i = 0; i < 26; i++)
        trie_release(t->child[i]);

    free(t);
}

/* push letter 'c' and return list head */
static list_t *list_push(list_t *obj, char c)
{
    list_t *newl = malloc(sizeof(list_t));
    newl->c = c;
    newl->next = obj;
    return newl;
}

static inline void list_release(list_t *obj)
{
    while (obj) {
        list_t *del = obj;
        obj = obj->next;
        free(del);
    }
}

StreamChecker *streamCheckerCreate(char **words, int words_sz)
{
    StreamChecker *obj = malloc(sizeof(StreamChecker));
    obj->t = calloc(1, sizeof(trie_t));
    obj->lh = NULL;
    for (int i = 0; i < words_sz; i++)
        trie_add_backward(obj->t, words[i]);

    return obj;
}

bool streamCheckerQuery(StreamChecker *obj, char letter)
{
    obj->lh = list_push(obj->lh, letter);
    return trie_check(obj->t, obj->lh);
}

void streamCheckerFree(StreamChecker *obj)
{
    trie_release(obj->t);
    list_release(obj->lh);
    free(obj);
}

/**
 * Your StreamChecker struct will be instantiated and called as such:
 * StreamChecker* obj = streamCheckerCreate(words, wordsSize);
 * bool param_1 = streamCheckerQuery(obj, letter);

 * streamCheckerFree(obj);
*/