
typedef struct __dlist
{
    struct __dlist *prev;
    struct __dlist *next;
    int idx;
} dlist_t;

/* double-ended Queue DS */
typedef struct __deque
{
    dlist_t *head;
    dlist_t *tail;
} deque_t;

#define DEQ_IS_EMPTY(X)  (!(X->head))
#define DEQ_GET_FRONT(X) (X->head->idx)
#define DEQ_GET_REAR(X)  (X->tail->idx)
#define DEQ_POP_FRONT(dq) do { \
    if (dq->head && dq->head == dq->tail) { \
        free(dq->head); \
        dq->tail = dq->head = NULL; \
    } else {    \
        dlist_t *tmp = dq->head->next; \
        free(dq->head); \
        dq->head = tmp; \
        tmp->prev = NULL; \
    } \
} while(0)

#define DEQ_POP_REAR(dq) do { \
    if (dq->head && dq->head == dq->tail) { \
        free(dq->tail); \
        dq->tail = dq->head = NULL; \
    } else { \
        dlist_t *tmp = dq->tail->prev; \
        free(dq->tail); \
        dq->tail = tmp; \
        tmp->next = NULL; \
    } \
} while(0)

#define DEQ_PUSH_REAR(dq, IDX) do { \
    dlist_t *n = calloc(1, sizeof(dlist_t)); \
    n->idx = IDX; \
    if (!dq->head) { \
        dq->head = dq->tail = n; \
    } else { \
        dq->tail->next = n; \
        n->prev = dq->tail; \
        dq->tail = n; \
    } \
} while(0)

#define DEQ_DESTROY(dq) do { \
    dlist_t *root = dq->head; \
    while (root) { \
        dlist_t *del = root; \
        root = root->next; \
        free(del); \
    } \
    free(dq); \
} while(0)

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
    int *ret = malloc(sizeof(int)*(numsSize - k + 1));
    int ret_ctr = 0;

    deque_t *dq = calloc(1, sizeof(deque_t));
    for (int i = 0; i < k; i++) {
        while (!DEQ_IS_EMPTY(dq) && nums[i] >= nums[DEQ_GET_REAR(dq)]) {
            DEQ_POP_REAR(dq);
        }
        DEQ_PUSH_REAR(dq, i);
    }
    ret[ret_ctr++] = nums[DEQ_GET_FRONT(dq)];

    for (int i = k; i < numsSize; i++) {
        if (DEQ_GET_FRONT(dq) == i - k) {
            DEQ_POP_FRONT(dq);
        }
        while (!DEQ_IS_EMPTY(dq) && nums[i] >= nums[DEQ_GET_REAR(dq)]) {
            DEQ_POP_REAR(dq);
        }

        DEQ_PUSH_REAR(dq, i);
        ret[ret_ctr++] = nums[DEQ_GET_FRONT(dq)];
    }

    DEQ_DESTROY(dq);
    *returnSize = ret_ctr;
    return ret;
}

