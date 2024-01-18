typedef struct {
    int rear;
    int front;
    int cur_sz;
    int size;
    int *data;
} MyStack;

#define MAX_CALLS (100)

MyStack* myStackCreate() {
    MyStack* obj = malloc(sizeof(MyStack));
    obj->size = MAX_CALLS + 1;
    obj->cur_sz = 0;
    obj->rear = 0;
    obj->front = 0;
    obj->data = malloc(sizeof(int)*obj->size);
    return obj;
}

static bool q_is_empty(MyStack* obj)
{
    return (obj->cur_sz == 0);
}

static int q_top(MyStack* obj)
{
    return obj->data[obj->front];
}

static int q_pop(MyStack* obj)
{
    int ret = obj->data[obj->front];
    obj->front = (obj->front + 1) % obj->size;
    obj->cur_sz--;
    return ret;
}

static void q_push(MyStack* obj, int val)
{
    obj->data[obj->rear] = val;
    obj->rear = (obj->rear + 1) % obj->size;
    obj->cur_sz++;
}

void myStackPush(MyStack* obj, int x)
{
    q_push(obj, x);
    for (int i = 0; i < obj->cur_sz - 1; i++) {
        int tmp = q_pop(obj);
        q_push(obj, tmp);
    }
}

int myStackPop(MyStack* obj)
{
    return q_pop(obj);
}

int myStackTop(MyStack* obj)
{
    return q_top(obj);
}

bool myStackEmpty(MyStack* obj)
{
    return q_is_empty(obj);
}

void myStackFree(MyStack* obj)
{
    free(obj->data);
    free(obj);
}

