
typedef struct {
    int cur_min;
    int val;
} data_t;

typedef struct {
    int ctr;
    data_t arr[30001];
} MinStack;


MinStack* minStackCreate() {
    return calloc(1, sizeof(MinStack));
}

static inline bool stack_is_empty(MinStack* obj)
{
    return (obj->ctr == 0);
}

int minStackGetMin(MinStack* obj)
{
    return obj->arr[obj->ctr - 1].cur_min;    
}

int minStackTop(MinStack* obj)
{
    return obj->arr[obj->ctr - 1].val;
}

void minStackPush(MinStack* obj, int val)
{
    int tmp_min = val;
    obj->arr[obj->ctr].val = val;
    if (!stack_is_empty(obj) && (minStackGetMin(obj) < tmp_min))
        obj->arr[obj->ctr].cur_min = minStackGetMin(obj);
    else
        obj->arr[obj->ctr].cur_min = val;
    obj->ctr += 1;
}

void minStackPop(MinStack* obj)
{
    obj->ctr -= 1;
}

void minStackFree(MinStack* obj)
{
    free(obj);    
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
 */
