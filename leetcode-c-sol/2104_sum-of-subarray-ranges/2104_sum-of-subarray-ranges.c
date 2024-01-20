typedef struct __list {
    int val;
    struct __list *next;
} list_t;

static list_t* stack_init()
{
    list_t *stack = calloc(1, sizeof(list_t));
    return stack;
}

static bool stack_is_empty(list_t *s)
{
    return (s->next == NULL);
}

static void stack_push(list_t *s, int idx)
{
    list_t *node = calloc(1, sizeof(list_t));
    node->val = idx;
    node->next = s->next;
    s->next = node;
}

static int stack_top(list_t *s)
{
    return (s->next)->val;
}

static void stack_pop(list_t *s)
{
    list_t *tmp = s->next;
    s->next = (s->next)->next;
    free(tmp);
}

static void stack_free(list_t *s)
{
    while (s) {
        list_t *tmp = s->next;
        free(s);
        s = tmp;
    }
}

long long subArrayRanges(int* nums, int numsSize)
{
    long long *sum = malloc(sizeof(long long)*numsSize);
    list_t *stack_min = stack_init();
    list_t *stack_max = stack_init();
    long long ret = 0;
    for (int i = 0; i < numsSize; i++) {
        while (!stack_is_empty(stack_min) && nums[i] < nums[stack_top(stack_min)])
            stack_pop(stack_min);

        if (stack_is_empty(stack_min))
            sum[i] = ((long long)(i + 1) * nums[i]);
        else
            sum[i] = (sum[stack_top(stack_min)] + (long long)(i - stack_top(stack_min)) * nums[i]);

        stack_push(stack_min, i);
        ret = (ret - sum[i]);
    }

    for (int i = 0; i < numsSize; i++) {
        while (!stack_is_empty(stack_max) && nums[i] > nums[stack_top(stack_max)])
            stack_pop(stack_max);

        if (stack_is_empty(stack_max))
            sum[i] = ((long long)(i + 1) * nums[i]);
        else
            sum[i] = (sum[stack_top(stack_max)] + (long long)(i - stack_top(stack_max)) * nums[i]);

        stack_push(stack_max, i);
        ret = (ret + sum[i]);
    }


    free(sum);
    stack_free(stack_min);
    stack_free(stack_max);
    return ret;
}

