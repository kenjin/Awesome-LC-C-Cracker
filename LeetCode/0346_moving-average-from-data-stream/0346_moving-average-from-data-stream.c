
typedef struct __list_node {
    int val;
    struct __list_node *next;
} list_t;

typedef struct {
    list_t *head;
    list_t *tail;
    int sum;
    int cur_sz;
    int win_sz;
} MovingAverage;

static inline bool is_empty_q(MovingAverage *obj)
{
    return (obj->cur_sz == 0);
}

static inline bool is_full_q(MovingAverage *obj)
{
    return (obj->cur_sz == obj->win_sz);
}

static inline double cal_avg(MovingAverage *obj)
{
    return ((double) obj->sum / obj->cur_sz);
}

static inline void add_q(MovingAverage *obj, int val)
{
    /* remove head when the windows size is full */
    if (is_full_q(obj)) {
        list_t *del = obj->head;
        obj->head = obj->head->next;
        obj->sum -= del->val;
        obj->cur_sz -= 1;
        free(del);
    }

    list_t *newn = calloc(1, sizeof(list_t));
    newn->val = val;
    if (is_empty_q(obj)) {
        obj->head = obj->tail = newn;
    } else {
        obj->tail->next = newn;
        obj->tail = newn;
    }
    obj->sum += val;
    obj->cur_sz += 1;
}

MovingAverage *movingAverageCreate(int size)
{
    MovingAverage *obj = calloc(1, sizeof(MovingAverage));
    obj->win_sz = size;
    return obj;
}

double movingAverageNext(MovingAverage *obj, int val)
{
    add_q(obj, val);
    return cal_avg(obj);
}

void movingAverageFree(MovingAverage *obj)
{
    list_t *cur = obj->head;
    while (cur) {
        list_t *del = cur;
        cur = cur->next;
        free(del);
    }
    free(obj);
}

/**
 * Your MovingAverage struct will be instantiated and called as such:
 * MovingAverage* obj = movingAverageCreate(size);
 * double param_1 = movingAverageNext(obj, val);

 * movingAverageFree(obj);
*/