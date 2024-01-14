
typedef struct __trie {
    char done;
    struct __trie *t[26];
} trie_t;

static void free_trie(trie_t *root)
{
    if (!root)
        return;

    for (int i = 0; i < 26; i++)
        free_trie(root->t[i]);  
    free(root);
}

static char find_trie(trie_t *root, char *s)
{
    if (!root)
        return 0;
    if (*s)
        return find_trie(root->t[*s - 'a'], s+1);

    return (root->done);
}

static void add_trie(trie_t *root, char *s)
{
    while (*s) {
        if (NULL == root->t[*s - 'a'])
            root->t[*s - 'a'] = calloc(1, sizeof(trie_t));
        root = root->t[*s - 'a'];
        s++;
    }
    root->done = 1;
}

bool wordBreak(char* s, char** wordDict, int wordDictSize)
{
    trie_t *t = calloc(1, sizeof(trie_t));
    for (int i = 0; i < wordDictSize; i++)
        add_trie(t, wordDict[i]);

    int len = strlen(s);
    char *dp = calloc(len + 1, sizeof(char));
    dp[0] = true;
    for (int i = 0; i <= len; i++) {
        char tmp = s[i];
        s[i] = 0;
        for (int j = 0; j < i; j++) {
            if (dp[j] && find_trie(t, &s[j])) { 
                dp[i] = true;
                break;   
            }
        }
        s[i] = tmp;
    }

    char ret = dp[len];
    free(dp);
    free_trie(t);
    return ret;
}
