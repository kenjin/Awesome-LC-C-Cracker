typedef struct {
    int head;
    int tail;
} POS;
typedef struct {
    int size;
    int cur;
    POS *p;
} STACK;

static inline STACK *stack_create(int size)
{
    STACK *obj = malloc(sizeof(STACK));
    obj->size = size;
    obj->cur = -1;
    obj->p = malloc(sizeof(int) * size);
    return obj;
}

static inline bool stack_is_empty(STACK *obj)
{
    return (obj->cur == -1 ? true : false);
}

static inline void stack_push(STACK *obj, int head, int tail)
{
    obj->cur += 1;
    obj->p[obj->cur].head = head;
	obj->p[obj->cur].tail = tail;
}

static POS stack_pop(STACK *obj)
{
    obj->cur -= 1;
    return obj->p[obj->cur + 1];
}

static inline void stack_release(STACK *obj)
{
    free(obj->p);
    free(obj);
}

static inline int insert_word(STACK *stk, char *dst, char *src)
{
    POS cur = stack_pop(stk);
    int clen = cur.tail - cur.head + 1;
    memcpy(dst, &src[cur.head], sizeof(char)*clen);
    return clen;
}

char * reverseWords(char * s)
{
	int len = strlen(s);
	char *tmp = calloc(len+1, sizeof(char));
	strcpy(tmp, s);
	STACK *stk = stack_create(len+1);
	bool in_str = false;
	int head = 0, tail = 0;
	for (int i = 0; i <= len; i++) {
		if (!in_str && tmp[i] != ' ') {
			in_str = true;
			head = i;
		} else if ((in_str && tmp[i] == ' ') || i == len) {
			tail = i - 1;
			stack_push(stk, head, tail);
			in_str = false;
		}
	}
	int idx = 0;
	if (!stack_is_empty(stk))		
		idx += insert_word(stk, &s[idx], tmp);

	while (!stack_is_empty(stk)) {
		s[idx++] = ' ';		
		idx += insert_word(stk, &s[idx], tmp);
	}
	s[idx] = 0;

	free(tmp);
	stack_release(stk);
	return s;
}
