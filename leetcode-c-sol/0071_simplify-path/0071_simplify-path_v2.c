typedef struct linked_list
{
    char *str;
    struct linked_list *next;
} linked_list_t;

typedef struct
{
    linked_list_t top;
} stack_t;

stack_t* stack_init()
{
    stack_t *s = malloc(sizeof(stack_t));
    (s->top).next = NULL;
    return s;
}

void stack_deinit(stack_t *s)
{
    linked_list_t *root = (s->top).next, *tmp;
    while (root) {
        tmp = root->next;
        free(root->str);
        free(root);
        root = tmp;
    }
    free(s);
}

bool stack_is_empty(stack_t *s)
{
    return ((s->top).next == NULL);
}

void stack_push(stack_t *s, char *target, int target_len)
{
    linked_list_t *node = malloc(sizeof(linked_list_t));
    node->str = calloc(target_len + 1, sizeof(char));
    strncpy(node->str, target, target_len);
    node->next = s->top.next;
    s->top.next = node;
}

void stack_pop(stack_t *s)
{
    if (stack_is_empty(s))
        return;

    linked_list_t *tmp_next = (s->top.next)->next;
    free((s->top.next)->str);
    free(s->top.next);
    s->top.next = tmp_next;
}

void reverse(stack_t *s)
{
    linked_list_t *root = s->top.next, *prev = NULL;
    while (root) {
        linked_list_t *tmp_next = root->next;
        root->next = prev;
        prev = root;
        root = tmp_next;
    }
    s->top.next = prev;
}

char * simplifyPath(char * path)
{
    int len = strlen(path);
    if (!len)
        return path;

    stack_t *s = stack_init();

    char *tmp = NULL, *token = NULL, *delim = "/";
    tmp = calloc(len + 1, sizeof(char)); 
    strncpy(tmp, path, len);

    token = strtok(tmp, delim);
    while (token != NULL) {
        int token_len = strlen(token);
        if (token_len == 2 && !strcmp(token, "..")) {
            // Case: `..`
            stack_pop(s);
        } else if (token_len != 1 || strcmp(token, ".")) {
            // Case: general string which excludes `.`
            stack_push(s, token, token_len);
        }
        token = strtok(NULL, delim);
    }

    // Reverse to perform bottom-up path created
    reverse(s);

    // Prepare the result
    memset(path, 0, sizeof(char) * len);    
    if (stack_is_empty(s)) {
        strcat(path, delim);
    } else {
        linked_list_t *root = s->top.next;
        while (root)
        {
            strcat(path, delim);
            strcat(path, root->str);
            root =root->next;
        }
    }

    stack_deinit(s);
    return path;
}
