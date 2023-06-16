/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct TreeNode *next;
 *     struct TreeNode *random;
 * };
 */

typedef struct Node NODE;
typedef struct __bucket {
    NODE *key;
    NODE *val;
    char used;
} BUCKET;

typedef struct __hashset {
    BUCKET *bucket;
    int size;
} HASH;

static int get_list_len(NODE *head)
{
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

static void hash_add_ele(HASH *h, NODE *key, NODE *obj)
{
    int idx = (intptr_t)(key) % (h->size);
    while (h->bucket[idx].used)
        idx = (idx + 1) % (h->size);
    h->bucket[idx].used = 1;
    h->bucket[idx].key = key;
    h->bucket[idx].val = obj;
}
static NODE *hash_chk(HASH *h, NODE *key)
{
    int idx = (intptr_t)(key) % (h->size);
    while (h->bucket[idx].used) {
        if (h->bucket[idx].key == key)
            return h->bucket[idx].val;

        idx = (idx + 1) % (h->size);
    }
    return NULL;
}

struct Node *copyRandomList(struct Node *head)
{
    int len = get_list_len(head);
    if (!len)
        return NULL;
    /* Init hash set */
    HASH *h = malloc(sizeof(HASH));
    h->bucket = calloc(len + 1, sizeof(BUCKET));
    h->size = len + 1;
    /* Update linked list node to hash set */
    NODE *cur = head;
    while (cur) {
        NODE *obj = malloc(sizeof(NODE));
        obj->val = cur->val;
        hash_add_ele(h, cur, obj);
        cur = cur->next;
    }
    /* Copy nodes */
    cur = head;
    while (cur) {
        NODE *obj = hash_chk(h, cur);
        obj->next = (cur->next ? hash_chk(h, cur->next) : NULL);
        obj->random = (cur->random ? hash_chk(h, cur->random) : NULL);
        cur = cur->next;
    }

    NODE *ret = hash_chk(h, head);
    /* release hashset */
    free(h->bucket);
    free(h);

    return ret;
}
