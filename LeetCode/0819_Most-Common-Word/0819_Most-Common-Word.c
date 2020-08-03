#define TYPE_EMPTY (-1)
#define TYPE_BAN (-2)
#define MAX_STR_LEN (101)

typedef struct __datainfo {
    int ctr;
    char str[MAX_STR_LEN]
} DATA;

typedef struct __hashinfo {
    int idx;
    char str[MAX_STR_LEN];
} HASH_NODE;

typedef struct __hash {
    HASH_NODE *arr;
    int size;
} HASH;

static int hash(HASH *obj, char *str)
{
    size_t hash = 5381;
    while (*str)
        hash = 33 * hash ^ (unsigned char) *str++;

    return hash % obj->size;
}

static inline HASH *hash_create(int size)
{
    HASH *obj = malloc(sizeof(HASH));
    obj->size = size;
    obj->arr = calloc(size, sizeof(HASH_NODE));
    for (int x = 0; x < size; x++)
        obj->arr[x].idx = TYPE_EMPTY;

    return obj;
}

static void hash_add(HASH *ht, char *key, int idx)
{
    int key_len = strlen(key);
    int index = hash(ht, key);
    while (ht->arr[index].idx != TYPE_EMPTY)
        index = (index + 1) % (ht->size);

    ht->arr[index].idx = idx;
    strncpy(ht->arr[index].str, key, key_len);
}

static int hash_find(HASH *ht, char *key)
{
    int key_len = strlen(key);
    int index = hash(ht, key);
    while (ht->arr[index].idx != TYPE_EMPTY) {
        if (!strncasecmp(ht->arr[index].str, key, key_len))
            return ht->arr[index].idx;
        index = (index + 1) % (ht->size);
    }
    return TYPE_EMPTY;
}

static inline void hash_release(HASH *ht)
{
    free(ht->arr);
    free(ht);
}

char *mostCommonWord(char *paragraph, char **banned, int bannedSize)
{
    HASH *h = hash_create(500);
    DATA d[MAX_STR_LEN];
    int data_sz = 0;

    for (int x = 0; x < bannedSize; x++)
        hash_add(h, banned[x], TYPE_BAN);

    /* transfer the string to lowercase */
    for (int x = 0; x < strlen(paragraph); x++) {
        if (paragraph[x] >= 'A' && paragraph[x] <= 'Z')
            paragraph[x] = paragraph[x] - 'A' + 'a';
    }

    char *delim = " ,.!?;:'", *pch = NULL;
    pch = strtok(paragraph, delim);
    int max_idx = 0;
    while (pch != NULL) {
        int ret = hash_find(h, pch);
        if (TYPE_EMPTY == ret) {
            d[data_sz].ctr = 1;
            sprintf(d[data_sz].str, "%s", pch);
            hash_add(h, pch, data_sz);
            data_sz++;
        } else if (TYPE_BAN != ret) {
            d[ret].ctr += 1;
            if (d[ret].ctr > d[max_idx].ctr)
                max_idx = ret;
        }
        pch = strtok(NULL, delim);
    }

    hash_release(h);
    char *ret = calloc(strlen(d[max_idx].str) + 1, sizeof(char));
    strcpy(ret, d[max_idx].str);
    return ret;
}
