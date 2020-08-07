

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
