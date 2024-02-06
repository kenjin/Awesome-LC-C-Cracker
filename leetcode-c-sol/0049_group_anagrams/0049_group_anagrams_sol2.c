#define MAX_STR_LEN 100 /* 0 <= strs[i].length <= 100 */

typedef struct __trie{
    int ret_idx;
    struct __trie *t[26];
} trie_t;

static inline trie_t* create_trie(void)
{
    return calloc(1, sizeof(trie_t));
}

static inline void free_trie(trie_t *root)
{
    if (!root)
        return;

    for (int i = 0; i < 26; i++) {
        free_trie(root->t[i]);
    }
    free(root);
}

static void add_trie(trie_t *obj, char *s, int idx)
{
    for (int i = 0; s[i] != 0; i++) {
        if (NULL == obj->t[s[i]-'a']) {
            obj->t[s[i]-'a'] = calloc(1, sizeof(trie_t));
        }
        obj = obj->t[s[i]-'a'];
    }

    obj->ret_idx = idx + 1;
}

static int find_trie(trie_t *obj, char *s)
{
    for (int i = 0; s[i] != 0; i++) {
        if (NULL == obj->t[s[i]-'a']) {
            return -1;
        }
        obj = obj->t[s[i]-'a'];
    }
    return obj->ret_idx - 1;
}

static void sort_str(char *s)
{
    int h[26] = {0};
    char *tmp = s;
    while (*s) {
        h[*s - 'a']++;
        s++;
    }

    for (int i = 0; i < 26; i++) {
        while (h[i]) {
            *tmp = i + 'a';
            tmp++;
            h[i]--;
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes)
{
    char str_tmp[MAX_STR_LEN+1] = {0};

    trie_t *root = create_trie();
    char ***ret = malloc(strsSize * sizeof(char **));
    *returnColumnSizes = calloc(strsSize, sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < strsSize; i++) {
        int len = strlen(strs[i]);
        snprintf(str_tmp, len+1, "%s", strs[i]);
        sort_str(str_tmp);
        int ret_idx = find_trie(root, str_tmp);
        if (ret_idx == -1) {
            add_trie(root, str_tmp, *returnSize);
            ret[*returnSize] = malloc(sizeof(char *));
            (*returnColumnSizes)[*returnSize] = 1;
            ret[*returnSize][0] = strs[i];
            *returnSize += 1;
        } else {
            (*returnColumnSizes)[ret_idx] += 1;
            ret[ret_idx] = realloc(ret[ret_idx], (*returnColumnSizes)[ret_idx] * sizeof(char *));
            ret[ret_idx][(*returnColumnSizes)[ret_idx]-1] = strs[i];   
        }
    }

    free_trie(root);
    return ret;
}
