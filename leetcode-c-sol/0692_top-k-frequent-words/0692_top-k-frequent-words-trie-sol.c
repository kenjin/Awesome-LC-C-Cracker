typedef struct __candidates_info {
    char *s;
    int freq;
} candidates_t;

typedef struct __word_info {
    int idx;
    int used;
} winfo_t;

typedef struct __trie {
    winfo_t winfo;
    struct __trie *t[26];
} trie_t;

static inline trie_t* create_trie(void)
{
    return calloc(1, sizeof(trie_t));
}

static void free_trie(trie_t *root)
{
    if (!root)
        return;

    for (int i = 0; i < 26; i++)
        free_trie(root->t[i]);  
    free(root);
}

static int find_trie(trie_t *root, char *s)
{
    if (!root)
        return -1;
    if (*s)
        return find_trie(root->t[*s - 'a'], s+1);

    return (root->winfo.used == 0 ? -1 : root->winfo.idx);
}

static void add_trie(trie_t *root, char *s, int s_idx)
{
    while (*s) {
        if (NULL == root->t[*s - 'a'])
            root->t[*s - 'a'] = calloc(1, sizeof(trie_t));
        root = root->t[*s - 'a'];
        s++;
    }
    root->winfo.idx = s_idx;
    root->winfo.used = 1;
}

static int compare(const void *a, const void *b)
{
    candidates_t r1 = *(candidates_t *)a;
    candidates_t r2 = *(candidates_t *)b;
    if (r1.freq == r2.freq) {
        return strcmp(r1.s, r2.s);
    }
    return (*(candidates_t *)b).freq - (*(candidates_t *)a).freq;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** topKFrequent(char** words, int wordsSize, int k, int* returnSize)
{
    trie_t *t = create_trie();
    candidates_t *candidates = malloc(sizeof(candidates_t)*wordsSize);
    int cand_idx = 0;
    for (int i = 0; i < wordsSize; i++) {
        int find_res = find_trie(t, words[i]);
        if (find_res >= 0) {
            candidates[find_res].freq += 1;
        } else {
            add_trie(t, words[i], cand_idx);
            candidates[cand_idx].s = words[i];
            candidates[cand_idx].freq = 1;
            cand_idx++;
        }
    }

    qsort(candidates, cand_idx, sizeof(candidates_t), compare);

    char **topk = malloc(sizeof(char *)*k);
    for (int i = 0; i < k; i++) {
        topk[i] = candidates[i].s;
    }

    *returnSize = k;
    free(candidates);
    free_trie(t);
    return topk;
}
