#if 0
typedef struct __list_data {
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

static void stack_push(STACK *obj, int val)
{
    DATA *new_node = calloc(1, sizeof(DATA));
    new_node->val = val;
    if (obj->head)
        new_node->next = obj->head;

    obj->head = new_node;
}

static inline bool stack_is_empty(STACK *obj)
{
    return (obj->head == NULL);
}

static void stack_pop(STACK *obj)
{
    DATA *del = obj->head;
    obj->head = del->next;
    free(del);
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
#endif

typedef struct __list {
    int val;
    struct __list *next;
    struct __list *prev;
} NODE;

typedef struct {
    NODE *top;
    int size;
} STACK;

STACK *stack_create()
{
    STACK *obj = calloc(1, sizeof(STACK));
    return obj;
}

void stack_push(STACK *obj, int x)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->val = x;
    new_node->next = NULL;
    NODE *tmp = obj->top;
    new_node->prev = tmp;
    if (tmp)
        tmp->next = new_node;

    obj->top = new_node;
}

int stack_pop(STACK *obj)
{
    int ret = obj->top->val;
    NODE *del = obj->top;
    obj->top = obj->top->prev;
    if (del->prev)
        obj->top->next = NULL;

    free(del);
    return ret;
}

int stack_top(STACK *obj)
{
    return obj->top->val;
}

bool stack_is_empty(STACK *obj)
{
    return (obj->top == NULL);
}

void stack_release(STACK *obj)
{
    NODE *tmp = obj->top;
    while (tmp) {
        NODE *del = tmp;
        tmp = tmp->next;
        free(del);
    }
    free(obj);
}
