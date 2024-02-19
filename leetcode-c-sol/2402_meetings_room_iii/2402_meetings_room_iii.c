/***

Approach: Heap

Clearly, we first need to keep track of which rooms are currently occupied and
how many meetings have been scheduled in each room.

Furthermore, to determine the point in time to which subsequent meetings should
be delayed if necessary, we need to record the end times of all meetings
currently in progress. Since the earliest ending meeting will be replaced by
later meetings, the data structure used for recording needs to dynamically
maintain the minimum value among all end times, and a min_heap(priority queue)
can fulfill this scenario.

Process the data itself, we need to sort them ourselves
in ascending order of start time. (This problem does not guarantee that the
given meeting times will be sorted by start time)

Then iterate over each meeting after sorting:
Suppose the current meeting is m, with time interval [L, R). If it is observed
that the minimum value in the min_heap (the meeting that ends earliest) starts
before m, i.e., "the earliest end time" ≤ L, then m will be scheduled in the
room of this ended meeting. The judgment condition includes the case of "="
because the meeting time is a half-closed interval, so the end time itself can
accommodate the start of another meeting; or if the number of elements in the
min_heap reaches n, meaning all rooms are occupied, then the room of the
earliest ending meeting must be vacated.

If only the latter condition of the above situation is satisfied (all rooms are
occupied), it means the earliest ending time (denoted as X) is greater than L.
Therefore, we need to additionally adjust the time interval of m to [X, X + (R -
L)).

Regardless of whether the above situation occurs or not, at this stage, there
must be rooms available. Therefore,
we iterate from index 0 to index n - 1 to find which room is available (using
the rooms_usage for judgment). Suppose the found room is room i, then we
need to increment rooms_usage[i].ctr by 1, indicating that room i has one more
meeting scheduled. Then, we add the end time of m (either the original R or X +
(R - L), depending on whether the previous condition is met) and the room number
used to the min_heap.

***/

typedef struct {
    int used;
    int ctr;
} room_t;

typedef struct {
    long long** arr;
    int cur_sz;
    int sz;
} heap_t;

#define MAX(a, b) (a > b ? a : b)

static inline int* heap_size(heap_t* obj) { return obj->cur_sz; }
static inline bool heap_is_empty(heap_t* obj) { return (heap_size(obj) == 0); }
static inline long long* heap_top(heap_t* obj) { return obj->arr[0]; }

static inline heap_t* heap_init(int sz) {
    heap_t* obj = malloc(sizeof(heap_t));
    obj->arr = malloc(sizeof(long long*) * sz);
    for (int i = 0; i < sz; i++)
        obj->arr[i] = malloc(sizeof(long long) * 2);
    obj->cur_sz = 0;
    obj->sz = sz;
    return obj;
}

static inline void heap_dinit(heap_t* obj) {
    for (int i = 0; i < obj->sz; i++)
        free(obj->arr[i]);
    free(obj->arr);
    free(obj);
}

static inline void swap(long long** a, long long** b) {
    long long* tmp = *a;
    *a = *b;
    *b = tmp;
}

static void min_heapify_bottom_up(long long** arr, int i) {
    int parent = ((i - 1) >> 1);
    if (parent >= 0) {
        if (arr[i][0] < arr[parent][0] ||
            (arr[i][0] == arr[parent][0] && arr[i][1] < arr[parent][1])) {
            swap(&arr[i], &arr[parent]);
            min_heapify_bottom_up(arr, parent);
        }
    }
}

static void min_heapify(long long** arr, int cur, int size) {
    int l_chd = (cur << 1) + 1;
    int r_chd = (cur << 1) + 2;
    int min = cur;
    if (l_chd < size &&
        (arr[l_chd][0] < arr[min][0] ||
         (arr[l_chd][0] == arr[min][0] && arr[l_chd][1] < arr[min][1])))
        min = l_chd;
    if (r_chd < size &&
        (arr[r_chd][0] < arr[min][0] ||
         (arr[r_chd][0] == arr[min][0] && arr[r_chd][1] < arr[min][1])))
        min = r_chd;

    if (min != cur) {
        swap(&arr[min], &arr[cur]);
        min_heapify(arr, min, size);
    }
}

static void heap_pop(heap_t* obj) {
    obj->arr[0][0] = obj->arr[obj->cur_sz - 1][0];
    obj->arr[0][1] = obj->arr[obj->cur_sz - 1][1];
    obj->cur_sz -= 1;
    min_heapify(obj->arr, 0, obj->cur_sz);
}

static void heap_push(heap_t* obj, long time, long id) {

    obj->arr[obj->cur_sz][0] = time;
    obj->arr[obj->cur_sz][1] = id;

    min_heapify_bottom_up(obj->arr, obj->cur_sz);
    obj->cur_sz += 1;
}

static int compare(const void* a, const void* b) {
    return (*(int**)a)[0] - (*(int**)b)[0];
}

int mostBooked(int n, int** meetings, int meetingsSize, int* meetingsColSize) {
    qsort(meetings, meetingsSize, sizeof(int*), compare);
    heap_t* occupied = heap_init(n);
    room_t* rooms_usage = calloc(n, sizeof(room_t));
    // Note: use long long to avoid integer overflow
    long long begin_t_adjusted = 0;
    for (int i = 0; i < meetingsSize; i++) {
        long long cur_meeting_head = (long long)meetings[i][0];
        long long cur_meeting_tail = (long long)meetings[i][1];
        begin_t_adjusted = MAX(begin_t_adjusted, cur_meeting_head);
        while (!heap_is_empty(occupied) &&
               (heap_size(occupied) == n ||
                begin_t_adjusted >= (heap_top(occupied))[0])) {
            long long* occu_top = heap_top(occupied);
            begin_t_adjusted = MAX(begin_t_adjusted, occu_top[0]);
            rooms_usage[occu_top[1]].used = 0;
            heap_pop(occupied);
        }

        for (int rid = 0; rid < n; rid++) {
            if (0 == rooms_usage[rid].used) {
                long long ending_time =
                    begin_t_adjusted + cur_meeting_tail - cur_meeting_head;
                rooms_usage[rid].used = 1;
                rooms_usage[rid].ctr += 1;
                heap_push(occupied, ending_time, rid);
                break;
            }
        }
    }

    int ret = 0;
    for (int rid = 0; rid < n; rid++) {
        if (rooms_usage[rid].ctr > rooms_usage[ret].ctr)
            ret = rid;
    }

    free(rooms_usage);
    heap_dinit(occupied);
    return ret;
}
