#define HASH_SIZE 10000
#define RHASH_MOD 8513
#define RHASH_BASE 26
#define HASH_MAP(_key, size) (_key % size)

typedef struct __ret_str_idx {
    int head;
    int tail;
} RET;

typedef struct __bucket_node {
    int head;
    int len;
    struct __bucket_node *next;
} NODE;

typedef struct {
    int size;
    NODE *bucket[HASH_SIZE];
} HASH;

static inline NODE *create_node()
{
    NODE *newNode = calloc(1, sizeof(NODE));
    return newNode;
}

static inline HASH *hash_init(int size)
{
    HASH *hash = calloc(1, sizeof(HASH));
    hash->size = size;
    return hash;
}

static void hash_insert(HASH *obj, int head, int len, int hash_idx)
{
    NODE *tmp = obj->bucket[HASH_MAP(hash_idx, obj->size)];
    NODE *newone = create_node();
    newone->head = head;
    newone->len = len;
    /* exist at least one node in current bucket */
    if (!tmp) {
        obj->bucket[hash_idx] = newone;
        return;
    }

    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = newone;
}

static bool hash_find(HASH *obj, char *src_str, char *cur_str, int hash_idx)
{
    NODE *tmp = obj->bucket[HASH_MAP(hash_idx, obj->size)];
    while (tmp != NULL) {
        if (tmp->len != 0 && !memcmp(&src_str[tmp->head], cur_str, tmp->len)) {
            return true;
        }
        tmp = tmp->next;
    }

    return false;
}

static void hash_free(HASH *obj)
{
    for (int i = 0; i < obj->size; i++) {
        NODE *tmp = obj->bucket[i];
        while (tmp) {
            NODE *delNode = tmp;
            tmp = tmp->next;
            free(delNode);
        }
    }
    free(obj);
}

/* rolling hash */
static long cal_rollhash(char *s, int len)
{
    long h = 0;
    for (int x = 0; x < len; x++)
        h = (RHASH_BASE * h + RHASH_MOD + s[x] - 'a') % RHASH_MOD;
    return h;
}

/**
 * @brief Check the longest duplicate substring
 * @return -1 on checking failed or head index of LPS
 */
static int check_lps(char *s, int slen, int clen)
{
    if (clen == 0)
        return -1;

    int ret = -1;
    HASH *h = hash_init(HASH_SIZE);
    long max_pow = 1l;

    for (int i = 1; i < clen; i++)
        max_pow = (RHASH_BASE * max_pow) % RHASH_MOD;

    /*
     * - Insert first string to hash table
     * - Calculate the rolling hash key of first string
     */
    long rh_key = cal_rollhash(s, clen);
    hash_insert(h, 0, clen, rh_key);

    for (int i = 1; (i + clen) <= slen; i++) {
        /* do rolling hash */
        rh_key = (rh_key + RHASH_MOD - max_pow * (s[i - 1] - 'a') % RHASH_MOD) %
                 RHASH_MOD;
        rh_key = (rh_key * RHASH_BASE + s[i + clen - 1] - 'a') % RHASH_MOD;
        if (hash_find(h, s, &s[i], rh_key)) {
            ret = i;
            break;
        } else
            hash_insert(h, i, clen, rh_key);
    }

    hash_free(h);
    return ret;
}

char *longestDupSubstring(char *S)
{
    int slen = strlen(S);
    int left = 0, right = slen;
    RET ret = {.head = -1, .tail = -1};

    while (left <= right) {
        int mid = ((right - left) >> 1) + left;
        int tmp = check_lps(S, slen, mid);
        if (tmp != -1) {
            ret.head = tmp;
            ret.tail = tmp + mid - 1;
            left = mid + 1;
        } else
            right = mid - 1;
    }

    if (-1 != ret.head) {
        S[ret.tail + 1] = 0;
        return &S[ret.head];
    }

    return "";
}