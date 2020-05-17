
typedef struct _stack {
    char *arr;
    int cur;
    int size;
} STACK;

static inline STACK *s_create(int size)
{
    STACK *s = malloc(sizeof(STACK));
    s->arr = calloc(size, sizeof(char));
    s->size = size;
    s->cur = -1;
    return s;
}

static inline void s_free(STACK *s)
{
    free(s->arr);
    free(s);
}

static inline char s_top(STACK *s)
{
    return s->arr[s->cur];
}

static inline bool s_is_empty(STACK *s)
{
    return (s->cur == -1);
}

static inline void s_put(STACK *s, char c)
{
    s->cur++;
    s->arr[s->cur] = c;
}

static inline void s_pop(STACK *s)
{
    s->cur--;
}

char *removeKdigits(char *num, int k)
{
    int len = strlen(num);
    STACK *s = s_create(len);

    int idx = 0;
    while (idx < len && k > 0) {
        if (s_is_empty(s)) {
            s_put(s, num[idx++]);
        } else if (s_top(s) > num[idx]) {
            s_pop(s);
            k--;
        } else {
            /* s_top(s) == num[idx] */
            s_put(s, num[idx++]);
        }
    }

    while (idx < len)
        s_put(s, num[idx++]);

    while (k > 0) {
        s_pop(s);
        k--;
    }

    /* remove leading zero */
    int lead_zero = 1, ret_ctr = 0;
    for (int x = 0; x <= s->cur; x++) {
        if (lead_zero && s->arr[x] == '0') {
            continue;
        } else
            lead_zero = 0;

        num[ret_ctr++] = s->arr[x];
    }
    num[ret_ctr] = 0;

    s_free(s);
    return (lead_zero ? "0" : num);
}
