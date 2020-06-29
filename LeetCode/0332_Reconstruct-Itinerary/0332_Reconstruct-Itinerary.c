#define HASH_SIZE 10000
#define IATA_CODE_SIZE 4
#define START_IATA_CODE "JFK"

typedef struct __bucket_node {
    char src[IATA_CODE_SIZE];
    int idx;  /* the first index of tickets that "from" is src */
    int size; /* the total size of tickets that "from" is src */
    struct __bucket_node *next;
} NODE;

typedef struct {
    int size;
    NODE **bucket;
} HASH;

static inline NODE *create_node()
{
    NODE *new_node = calloc(1, sizeof(NODE));
    new_node->size = 1;
    return new_node;
}

static inline HASH *hash_init(int size)
{
    HASH *hash = calloc(1, sizeof(HASH));
    hash->size = size;
    hash->bucket = calloc(size, sizeof(NODE *));
    return hash;
}

static inline int do_hash(HASH *obj, char *str)
{
    size_t hash = 5381;
    while (*str)
        hash = 33 * hash ^ (unsigned char) *str++;

    return hash % obj->size;
}

static void hash_insert(HASH *obj, char *key, int idx)
{
    int hash_idx = do_hash(obj, key);
    NODE *tmp = obj->bucket[hash_idx];
    NODE *newone = create_node();
    newone->idx = idx;
    strncpy(newone->src, key, IATA_CODE_SIZE - 1);
    if (!tmp) {
        obj->bucket[hash_idx] = newone;
        return;
    }
    /* exist at least one node in current bucket */
    NODE *prev = NULL;
    while (tmp != NULL) {
        if (!strncmp(tmp->src, key, IATA_CODE_SIZE - 1)) {
            tmp->size++;
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    prev->next = newone;
}

static bool hash_find(HASH *obj, char *key, int *ret)
{
    int hash_idx = do_hash(obj, key);
    NODE *tmp = obj->bucket[hash_idx];
    while (tmp != NULL) {
        if (!strncmp(tmp->src, key, IATA_CODE_SIZE - 1)) {
            ret[0] = tmp->idx;
            ret[1] = tmp->size;
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

bool iata_dfs(HASH *h,
              char ***tickets,
              char **ret,
              int ret_sz,
              char *target,
              int idx,
              char *check)
{
    if (idx == ret_sz)
        return true;

    /**
     *  @findRet[0]: first index of tickets that "from" is target
     *  @findRet[1]: total size of tickets that "from" is target
     */
    int find_ret[2] = {0};
    if (!hash_find(h, target, find_ret))
        return false;

    int i = find_ret[0];
    bool found = false;
    while (i < find_ret[0] + find_ret[1]) {
        if (check[i]) {
            i++;
            continue;
        }
        /* update check flag */
        check[i] = 1;

        /* dfs */
        if (iata_dfs(h, tickets, ret, ret_sz, tickets[i][1], idx + 1, check)) {
            found = true;
            break;
        }

        /* recover check flag */
        check[i++] = 0;
    }

    if (!found)
        return false;

    ret[idx] = calloc(IATA_CODE_SIZE, sizeof(char));
    strcpy(ret[idx], tickets[i][1]);
    return true;
}

int compare(const void *a, const void *b)
{
    const char **s1 = *(char ***) a;
    const char **s2 = *(char ***) b;

    int ret = strcmp(s1[0], s2[0]);
    return (!ret ? strcmp(s1[1], s2[1]) : ret);
}

char **findItinerary(char ***tickets,
                     int ticketsSize,
                     int *ticketsColSize,
                     int *returnSize)
{
    /* Sort all tickets pair */
    qsort(tickets, ticketsSize, sizeof(char *), compare);

    /* Create hash data sructure */
    HASH *h = hash_init(HASH_SIZE);

    /* Use check pointer to record the tickets[i] is visited(or banned) */
    char *check = calloc(ticketsSize, sizeof(char));

    /* Add to hash */
    for (int i = 0; i < ticketsSize; i++)
        hash_insert(h, tickets[i][0], i);

    /* Init return variable */
    *returnSize = ticketsSize + 1;
    char **ret = malloc(sizeof(char *) * (*returnSize));

    /* Init node start from "JFK" */
    char start_code[IATA_CODE_SIZE] = {0};
    strcpy(start_code, START_IATA_CODE);
    ret[0] = calloc(IATA_CODE_SIZE, sizeof(char));
    strcpy(ret[0], start_code);

    /* DFS to update the result */
    iata_dfs(h, tickets, ret, *returnSize, start_code, 1, check);

    /* release memory*/
    free(check);
    hash_free(h);
    return ret;
}
