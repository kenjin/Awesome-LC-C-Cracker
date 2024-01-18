typedef struct __list {
    int val;
    struct __list *next;
} list_t;

typedef struct {
    list_t *s1;
    list_t *s2;
} MyQueue;

static bool s_is_empty(list_t *root)
{
    return (root->next == NULL ? true : false);
}

static int s_top(list_t *root)
{
    return root->next->val;
}

static int s_pop(list_t *root)
{
    list_t *del = root->next;
    int ret = del->val;
    root->next = root->next->next;
    free(del);
    return ret;
}

static void s_push(list_t *root, int val)
{
    list_t **indir = &root;
    list_t *node = calloc(1, sizeof(list_t));
    node->val = val;
    node->next = root->next;
    root->next = node;
}

static void s_free(list_t *root)
{
    while (root) {
        list_t *tmp = root->next;
        free(root);
        root = tmp;
    }
}

MyQueue* myQueueCreate()
{
    MyQueue* q = malloc(sizeof(MyQueue));
    q->s1 = calloc(1, sizeof(list_t));
    q->s2 = calloc(1, sizeof(list_t));
    return q;
}

void myQueuePush(MyQueue* obj, int x)
{
    while (!s_is_empty(obj->s1)) {
        int tmp = s_pop(obj->s1);
        s_push(obj->s2, tmp);    
    }
    s_push(obj->s1, x);
    while (!s_is_empty(obj->s2)) {
        int tmp = s_pop(obj->s2);
        s_push(obj->s1, tmp);    
    }
}

int myQueuePop(MyQueue* obj)
{
    return s_pop(obj->s1);
}

int myQueuePeek(MyQueue* obj)
{
    return s_top(obj->s1);
}

bool myQueueEmpty(MyQueue* obj)
{
    return s_is_empty(obj->s1);
}

void myQueueFree(MyQueue* obj)
{
    s_free(obj->s1);
    s_free(obj->s2);
}
