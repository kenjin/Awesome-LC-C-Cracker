
typedef struct {
    int head;
    int in_degree;
    int out_degree;
    int used;
} INFO;

typedef struct {
    int *arr;
    int size;
    int cur;
    int front;
    int rear;
} QUEUE;

static inline QUEUE *create_q(int size)
{
    QUEUE *q = malloc(sizeof(QUEUE));
    q->arr = malloc(sizeof(int) * size);
    q->size = size;
    q->cur = 0;
    q->front = 0;
    q->rear = -1;
    return q;
}

static inline void release_q(QUEUE *q)
{
    free(q->arr);
    free(q);
}

static inline bool empty_q(QUEUE *q)
{
    return (q->cur == 0);
}

static inline void add_q(QUEUE *q, int idx)
{
    q->rear = (q->rear + 1) % q->size;
    q->arr[q->rear] = idx;
    q->cur++;
}

static inline int del_q(QUEUE *q)
{
    int ret = q->arr[q->front];
    q->front = (q->front + 1) % q->size;
    q->cur--;
    return ret;
}

static int compare(const void *a, const void *b)
{
    int *n1 = *(int **) a;
    int *n2 = *(int **) b;
    return n1[1] - n2[1];
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

bool canFinish(int num_courses,
               int **prerequisites,
               int prerequisites_sz,
               int *prerequisites_colsz)
{
    qsort(prerequisites, prerequisites_sz, sizeof(int *), compare);

    INFO *info = calloc(num_courses, sizeof(INFO));
    for (int x = 0; x < prerequisites_sz; x++) {
        int src = prerequisites[x][1];
        int dst = prerequisites[x][0];
        if (!info[src].used) {
            info[src].used = 1;
            info[src].head = x;
        }
        info[src].out_degree += 1;
        info[dst].in_degree += 1;
    }

    QUEUE *q = create_q(num_courses);
    for (int x = 0; x < num_courses; x++) {
        if (info[x].in_degree == 0) {
            add_q(q, x);
        }
    }
    int ret_ctr = 0;
    /* Topology Sort */
    char *chk = calloc(num_courses, sizeof(char));
    while (!empty_q(q)) {
        int cur = del_q(q);
        ret_ctr++;
        chk[cur] = 1;
        int head = info[cur].head;
        int edges = info[cur].head + info[cur].out_degree - 1;
        for (int i = head; i <= edges; i++) {
            int tmp = prerequisites[i][0];
            info[tmp].in_degree -= 1;
            if (0 == info[tmp].in_degree)
                add_q(q, tmp);
        }
    }

    for (int i = 0; i < num_courses; i++) {
        if (!chk[i] && 0 == info[i].in_degree)
            ret_ctr++;
    }

    free(chk);
    release_q(q);
    return (ret_ctr == num_courses ? true : false);
}
