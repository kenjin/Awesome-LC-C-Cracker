typedef struct {
    int size;
    int cur;
    int *arr;
} STACK;

STACK *stack_create(int size)
{
    STACK *obj = malloc(sizeof(STACK));
    obj->size = size;
    obj->cur = -1;
    obj->arr = malloc(sizeof(int) * size);
    return obj;
}

static inline bool stack_is_empty(STACK *obj)
{
    return (obj->cur == -1 ? true : false);
}

static inline void stack_push(STACK *obj, int idx)
{
    obj->cur += 1;
    obj->arr[obj->cur] = idx;
}

static int stack_pop(STACK *obj)
{
    if (stack_is_empty(obj)) {
        printf("WARNING: empty stack!\n");
        return;
    }

    obj->cur -= 1;
    return obj->arr[obj->cur + 1];
}

static inline int stack_top(STACK *obj)
{
    if (stack_is_empty(obj))
        return -1;
    return obj->arr[obj->cur];
}

static inline void stackFree(STACK *obj)
{
    free(obj->arr);
    free(obj);
}

int trap(int *height, int height_sz)
{
    STACK *s = stack_create(height_sz + 1);

    int ret = 0;
    for (int i = 0; i < height_sz; i++) {
        if (stack_is_empty(s) && height[i] == 0)
            continue;

        if (!stack_is_empty(s)) {
            int top = height[stack_top(s)];
            if (height[i] > top) {
                int max_height = height[i];
                int lvalley_idx = stack_pop(s);
                while (!stack_is_empty(s)) {
                    int chk_idx = stack_pop(s);
                    int diff = (max_height > height[chk_idx])
                                   ? height[chk_idx] - height[lvalley_idx]
                                   : max_height - height[lvalley_idx];

                    if (!diff)
                        ret += diff * (i - chk_idx - 1);
                    if (max_height < height[chk_idx]) {
                        stack_push(s, chk_idx);
                        break;
                    }
                    lvalley_idx = chk_idx;
                }
            }
        }
        stack_push(s, i);
    }

    stackFree(s);
    return ret;
}
