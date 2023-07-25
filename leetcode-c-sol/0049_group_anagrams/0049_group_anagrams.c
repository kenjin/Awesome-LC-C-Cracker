#define MAX_STR_LEN 100 /* 0 <= strs[i].length <= 100 */

typedef struct _list{
    char *s_ptr;
    struct _list *next;
} list_t;

typedef struct {
    char str[MAX_STR_LEN + 1];
    int slen;
    int nums; /* record total nodes in this bucket */
    list_t head;
} hash_bucket_t;

typedef struct {
    int size;
    int group_cnt; /* record num of buckets in use */
    hash_bucket_t *buckets;
} hash_ctx_t;

static void do_sort_str(char *s)
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

static inline hash_ctx_t* create_hash_ctx(int size)
{
    hash_ctx_t *h_ctx = calloc(1, sizeof(hash_ctx_t));
    h_ctx->size = size;
    h_ctx->buckets = calloc(size, sizeof(hash_bucket_t));
    return h_ctx;
}

static inline void destroy_hash_ctx(hash_ctx_t *h_ctx)
{
    for (int i = 0; i < h_ctx->size; i++) {
        list_t *curr = h_ctx->buckets[i].head.next;
        while (curr) {
            list_t *tmp = curr->next;
            free(curr);
            curr = tmp;
        }
    }
    free(h_ctx->buckets);
    free(h_ctx);
}

static inline int do_hash(hash_ctx_t *h_ctx, char *str)
{
    size_t hash = 5381;
    while (*str)
        hash = 33 * hash ^ (unsigned char) *str++;

    return hash % h_ctx->size;
}

static void add_hash(hash_ctx_t *h_ctx, char *str, char *sorted_str, int slen)
{
    int idx = do_hash(h_ctx, sorted_str);
    while (h_ctx->buckets[idx].head.next != NULL) {
        if (slen == h_ctx->buckets[idx].slen && 0 == strncmp(h_ctx->buckets[idx].str, sorted_str, slen)) {
            // Add str to linkded list of existed bucket
            list_t *new_node = calloc(1, sizeof(list_t));
            new_node->s_ptr = str;
            new_node->next = h_ctx->buckets[idx].head.next;
            h_ctx->buckets[idx].head.next = new_node;
            h_ctx->buckets[idx].nums++;
            return;
        }
        idx= (idx + 1) % h_ctx->size;
    }

    // Add str to new bucket
    h_ctx->buckets[idx].slen = slen;
    strncpy(h_ctx->buckets[idx].str, sorted_str, slen);
    list_t *new_node = calloc(1, sizeof(list_t));
    new_node->s_ptr = str;
    h_ctx->buckets[idx].head.next = new_node; 
    h_ctx->buckets[idx].nums++;
    h_ctx->group_cnt++;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes)
{
    hash_ctx_t *h_ctx = create_hash_ctx(strsSize);
    char str_tmp[MAX_STR_LEN+1] = {0};

    for (int i = 0; i < strsSize; i++) {
        int len = strlen(strs[i]);
        snprintf(str_tmp, len + 1, "%s", strs[i]);
        do_sort_str(str_tmp);
        add_hash(h_ctx, strs[i], str_tmp, len);
    }

    char ***ret = malloc(h_ctx->group_cnt * sizeof(char **));
    *returnColumnSizes = malloc(h_ctx->group_cnt * sizeof(int));
    *returnSize = h_ctx->group_cnt;
    int ret_cnt = 0;
    for (int i = 0; i < h_ctx->size; i++) {
        if (h_ctx->buckets[i].nums == 0)
            continue;

        (*returnColumnSizes)[ret_cnt] = h_ctx->buckets[i].nums;
        ret[ret_cnt] = malloc(sizeof(char *) * h_ctx->buckets[i].nums);
        list_t *root = h_ctx->buckets[i].head.next;
        for (int x = 0; x < h_ctx->buckets[i].nums; x++) {
            ret[ret_cnt][x] = calloc(h_ctx->buckets[i].slen + 1, sizeof(char));
            strncpy(ret[ret_cnt][x], root->s_ptr, h_ctx->buckets[i].slen);
            root = root->next;
        }
        ret_cnt++;
    }

    destroy_hash_ctx(h_ctx);
    return ret;
}
