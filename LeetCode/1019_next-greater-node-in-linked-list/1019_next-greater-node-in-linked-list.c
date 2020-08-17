/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode NODE;

typedef struct __list_data {
    int idx;
    int val;
    struct __list_data *next;
} DATA;

typedef struct {
    DATA *head;
} STACK;

static inline STACK *stack_create()
{
    STACK *obj = malloc(sizeof(STACK));
    obj->head = NULL;
    return obj;
}

static void stack_push(STACK *obj, int idx, int val)
{
    DATA *new_node = calloc(1, sizeof(DATA));
    new_node->idx = idx;
    new_node->val = val;
    if (obj->head)
        new_node->next = obj->head;

    obj->head = new_node;
}

static inline bool stack_is_empty(STACK *obj)
{
    return (obj->head == NULL);
}

/* return node index of head data node */
static int stack_pop(STACK *obj)
{
    DATA *del = obj->head;
    int ret = del->idx;
    obj->head = del->next;
    free(del);
    return ret;
}
/* return value of head data node */
static int stack_top(STACK *obj)
{
    return obj->head->val;
}

static inline void stack_release(STACK *obj)
{
    DATA *cur = obj->head;
    while (cur) {
        DATA *del = cur;
        cur = cur->next;
        free(del);
    }
    free(obj);
}

static inline int get_list_size(NODE *head)
{
    int size = 0;
    while (head) {
        head = head->next;
        size++;
    }
    return size;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *nextLargerNodes(struct ListNode *head, int *returnSize)
{
    int list_sz = get_list_size(head);
    if (!list_sz) {
        *returnSize = 0;
        return NULL;
    }

    int *ret = malloc(sizeof(int) * list_sz);
    *returnSize = list_sz;
    STACK *s = stack_create();
    NODE *cur = head;
    int idx = 0;
    while (cur) {
        if (!stack_is_empty(s) && cur->val > stack_top(s)) {
            int up_idx = stack_pop(s);
            ret[up_idx] = cur->val;
        } else {
            stack_push(s, idx, cur->val);
            cur = cur->next;
            idx++;
        }
    }

    while (!stack_is_empty(s)) {
        int up_idx = stack_pop(s);
        ret[up_idx] = 0;
    }

    stack_release(s);
    return ret;
}