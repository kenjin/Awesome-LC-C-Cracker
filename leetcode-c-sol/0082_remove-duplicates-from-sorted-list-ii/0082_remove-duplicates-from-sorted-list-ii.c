/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode NODE;


static int get_list_sz(NODE *root)
{
    int len = 0;
    while (root) {
        len++;
        root = root->next;
    }
    return len;
}

typedef struct __data {
    int val;
    int ctr;
    int used;
} DATA;

typedef struct __hash {
    DATA *bucket;
    int size;
} HASH;

static inline HASH *create_hash(int size)
{
    HASH *obj = malloc(sizeof(HASH));
    obj->size = size;
    obj->bucket = calloc(size, sizeof(DATA));
    return obj;
}

static inline void release_hash(HASH *h)
{
    free(h->bucket);
    free(h);
}

static inline int do_hash(int val, int size)
{
    int ret = val % size;
    ret = (ret >= 0 ? ret : ret + size);
    return ret;
}

static inline int get_ctr_from_hash(HASH *h, int target)
{
    int idx = do_hash(target, h->size);
    while (h->bucket[idx].used) {
        if (h->bucket[idx].val == target)
            return h->bucket[idx].ctr;

        idx = (idx + 1) % h->size;
    }
    return -1;
}

static inline void update_hash(HASH *h, int val)
{
    int idx = do_hash(val, h->size);
    while (h->bucket[idx].used) {
        if (h->bucket[idx].val == val) {
            h->bucket[idx].ctr += 1;
            return;
        }
        idx = (idx + 1) % h->size;
    }
    h->bucket[idx].val = val;
    h->bucket[idx].ctr = 1;
    h->bucket[idx].used = 1;
}

struct ListNode *deleteDuplicates(struct ListNode *head)
{
    /* get list length to confirm the hash size */
    int list_sz = get_list_sz(head);
    /* use hash to record duplicates of node val */
    HASH *h = create_hash(list_sz + 1);
    NODE *cur = head, *prev = NULL;
    while (cur) {
        update_hash(h, cur->val);
        cur = cur->next;
    }

    cur = head;
    while (cur) {
        NODE *next_one = cur->next;
        /* check duplicates */
        if (get_ctr_from_hash(h, cur->val) > 1) {
            if (NULL == prev) {
                /* head case */
                head = next_one;
            } else {
                /* non-head case */
                prev->next = next_one;
                free(cur);
            }
            cur = next_one;
            continue;
        }
        /* normal case without duplicates */
        prev = cur;
        cur = next_one;
    }
    release_hash(h);
    return head;
}