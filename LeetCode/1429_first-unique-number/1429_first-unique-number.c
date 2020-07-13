
#define HASH_MAX_SIZE 50001 /* At most 50000 calls will be made to add */

typedef struct __doubly_linked_list {
    int val;
    struct __doubly_linked_list *prev;
    struct __doubly_linked_list *next;
} DLIST;

typedef struct {
    int val;
    int block;
    DLIST *dl;
} NODE;

typedef struct {
    NODE *n;
    int size;
} HASH;

typedef struct {
    HASH *h;
    DLIST *head;
} FirstUnique;

static inline DLIST *list_init_head()
{
    DLIST *head = malloc(sizeof(DLIST));
    head->next = head;
    head->prev = head;
    return head;
}

static inline int list_is_empty(DLIST *head)
{
    return (head->next == head);
}

static inline int list_get_first(DLIST *head)
{
    return head->next->val;
}

static inline void list_add_tail(DLIST *head, DLIST *node)
{
    DLIST *prev = head->prev;
    prev->next = node;
    node->prev = prev;
    node->next = head;
    head->prev = node;
}

static inline void list_del(DLIST *node)
{
    DLIST *next = node->next;
    DLIST *prev = node->prev;
    next->prev = prev;
    prev->next = next;
}

static inline void list_free(DLIST *head)
{
    DLIST *next = head->next;
    while (next != head) {
        DLIST *tmp = next->next;
        free(next);
        next = tmp;
    }
    free(head);
}


static inline HASH *hash_create(int size)
{
    HASH *h = malloc(sizeof(HASH));
    h->size = size;
    h->n = calloc(size, sizeof(NODE));
    return h;
}

static inline void hash_release(HASH *h)
{
    free(h->n);
    free(h);
}

static void hash_add(HASH *h, int val, DLIST *dl)
{
    int hash_idx = val % h->size;
    /* "1 <= value" so value "0" imply that the bucket is empty */
    if (h->n[hash_idx].val) {
        hash_idx = (hash_idx + 1) % h->size;
    }

    h->n[hash_idx].val = val;
    h->n[hash_idx].dl = dl;
}

static DLIST *hash_find_and_block(HASH *h, int val, int *block)
{
    DLIST *ret = NULL;
    int hash_idx = val % h->size;
    while (h->n[hash_idx].val) {
        if (h->n[hash_idx].val == val) {
            /* Block it to avoid the additional add */
            if (h->n[hash_idx].block)
                *block = 1;
            ret = h->n[hash_idx].dl;
            h->n[hash_idx].block = 1;
            break;
        }
        hash_idx = (hash_idx + 1) % h->size;
    }

    return ret;
}

int firstUniqueShowFirstUnique(FirstUnique *obj)
{
    if (list_is_empty(obj->head))
        return -1;

    return list_get_first(obj->head);
}

void firstUniqueAdd(FirstUnique *obj, int value)
{
    int block = 0;
    DLIST *res = hash_find_and_block(obj->h, value, &block);
    /* first element */
    if (!res) {
        DLIST *node = malloc(sizeof(DLIST));
        node->val = value;
        list_add_tail(obj->head, node);
        hash_add(obj->h, value, node);
    }
    if (res && !block) {
        /* remove from doubly linked list*/
        list_del(res);
        free(res);
    }
}

FirstUnique *firstUniqueCreate(int *nums, int numsSize)
{
    FirstUnique *obj = malloc(sizeof(FirstUnique));
    obj->h = hash_create(HASH_MAX_SIZE + numsSize);
    obj->head = list_init_head();
    for (int i = 0; i < numsSize; i++)
        firstUniqueAdd(obj, nums[i]);

    return obj;
}

void firstUniqueFree(FirstUnique *obj)
{
    list_free(obj->head);
    hash_release(obj->h);
    return;
}

/**
 * Your FirstUnique struct will be instantiated and called as such:
 * FirstUnique* obj = firstUniqueCreate(nums, numsSize);
 * int param_1 = firstUniqueShowFirstUnique(obj);

 * firstUniqueAdd(obj, value);

 * firstUniqueFree(obj);
*/