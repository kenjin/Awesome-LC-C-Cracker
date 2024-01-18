typedef struct __list {
    int val;
    struct __list *next;
} list_t;

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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize)
{
    int *ret = malloc(sizeof(int)*temperaturesSize);
    *returnSize = temperaturesSize;
    list_t stack = {.next = NULL};
    for (int i = 0; i < temperaturesSize; i++) {
        while (!s_is_empty(&stack) && temperatures[i] > temperatures[s_top(&stack)]) {
            int tmp = s_pop(&stack);
            ret[tmp] = i - tmp;
        }
        s_push(&stack, i);
    }

    while (!s_is_empty(&stack)) {
        int tmp = s_pop(&stack);
        ret[tmp] = 0;
    }

    s_free(stack.next);
    return ret;
}
