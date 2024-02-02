
typedef struct {
    int sz;
    int* buf;
    int rear;
    int front;
    int cur_sz;
} queue_t;

static queue_t* q_init(int sz) {
    queue_t* obj = malloc(sizeof(queue_t));
    obj->sz = sz;
    obj->buf = malloc(sizeof(int) * sz);
    obj->rear = 0;
    obj->front = 0;
    obj->cur_sz = 0;
    return obj;
}

static void q_dinit(queue_t* obj) {
    free(obj->buf);
    free(obj);
}

static bool q_is_empty(queue_t* obj) { return (obj->cur_sz == 0); }

static void q_enq(queue_t* obj, int val) {
    obj->buf[obj->rear] = val;
    obj->rear = (obj->rear + 1) % obj->sz;
    obj->cur_sz += 1;
}

static int q_deq(queue_t* obj) {
    int ret = obj->buf[obj->front];
    obj->front = (obj->front + 1) % obj->sz;
    obj->cur_sz -= 1;
    return ret;
}

static inline int get_digits(int val) {
    int ctr = 0;
    while (val) {
        val /= 10;
        ctr++;
    }
    return ctr;
}

int* sequentialDigits(int low, int high, int* returnSize)
{
    int max_d = get_digits(high);
    queue_t* q = q_init(10);

    // Init: Put 1 ~ 9 to queue
    for (int i = 1; i <= 9; i++)
        q_enq(q, i);

    int* ret = malloc(sizeof(int) * max_d * 10);
    *returnSize = 0;
    while (!q_is_empty(q)) {
        int cur_val = q_deq(q);
        if (cur_val > high)
            break;

        if (cur_val <= high && cur_val >= low) {
            ret[*returnSize] = cur_val;
            *returnSize += 1;
        }

        // Note that the second digit is at most 8, so the first digit could be
        // at most 9.
        if (cur_val % 10 < 9)
            q_enq(q, cur_val * 10 + (cur_val % 10) + 1);
    }

    ret = realloc(ret, sizeof(int) * (*returnSize));
    q_dinit(q);
    return ret;
}
