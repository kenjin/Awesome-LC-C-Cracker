/***

Approach: Priority Queue

Each round has a duration of n + 1. We prioritize inserting tasks with the
highest frequency. Thus, we utilize a priority queue to pop out tasks with the
highest frequency one by one. After popping out n + 1 tasks, if the round is
full, we decrement the frequency of those tasks that have been completed and
insert them back into the queue. This process continues until all task
frequencies become 0.

***/

typedef struct {
    int* arr;
    int sz;
} heap_t;

static inline void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline bool heap_is_empty(heap_t* obj) { return (obj->sz == 0); }

static void max_heapify(int* arr, int cur, int size) {
    int l_chd = (cur << 1) + 1;
    int r_chd = (cur << 1) + 2;
    int max = cur;
    if (l_chd < size && arr[l_chd] > arr[max])
        max = l_chd;
    if (r_chd < size && arr[r_chd] > arr[max])
        max = r_chd;

    if (max != cur) {
        swap(&arr[max], &arr[cur]);
        max_heapify(arr, max, size);
    }
}

static void max_heapify_bottom_up(int* arr, int i) {
    int parent = ((i - 1) >> 1);
    if (parent >= 0) {
        if (arr[i] > arr[parent]) {
            swap(&arr[i], &arr[parent]);
            max_heapify_bottom_up(arr, parent);
        }
    }
}

static void create_heap(int* arr, int size) {
    for (int i = ((size - 1) >> 1); i >= 0; i--)
        max_heapify(arr, i, size);
}

static int heap_pop(heap_t* obj) {
    int ret = obj->arr[0];
    obj->arr[0] = obj->arr[obj->sz - 1];
    obj->sz -= 1;
    max_heapify(obj->arr, 0, obj->sz);
    return ret;
}

static void heap_push(heap_t* obj, int val) {
    obj->arr[obj->sz] = val;
    max_heapify_bottom_up(obj->arr, obj->sz);
    obj->sz += 1;
}

static inline heap_t* heap_init(int* arr, int sz) {
    create_heap(arr, sz);
    heap_t* obj = malloc(sizeof(heap_t));
    obj->arr = arr;
    obj->sz = sz;
    return obj;
}

static inline void heap_dinit(heap_t* obj) { free(obj); }

int leastInterval(char* tasks, int tasksSize, int n) {
    int ret = 0;
    int task_ctr[26] = {0}, task_num = 0;

    for (int i = 0; i < tasksSize; i++)
        task_ctr[(tasks[i] - 'A')] += 1;

    for (int i = 0; i < 26; i++) {
        if (task_ctr[i])
            task_ctr[task_num++] = task_ctr[i];
    }

    heap_t* task_st = heap_init(task_ctr, task_num);
    int cycle = n + 1, times = 0;
    int queue[26] = {0};
    while (!heap_is_empty(task_st)) {
        int cur_time = 0, q_ctr = 0;
        for (int i = 0; i < cycle; i++) {
            if (!heap_is_empty(task_st)) {
                int cur = heap_pop(task_st);
                queue[q_ctr++] = cur;
                cur_time++;
            }
        }

        for (int i = 0; i < q_ctr; i++) {
            if (--queue[i])
                heap_push(task_st, queue[i]);
        }

        times += (!heap_is_empty(task_st) ? cycle : cur_time);
    }

    heap_dinit(task_st);
    return times;
}
