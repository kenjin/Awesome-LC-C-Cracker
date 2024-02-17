/***
Go through the array heights, for each building heights[i], determine if the
next building heights[i + 1] is greater than it.

If so, we define diff = heights[i + 1] - heights[i]. Then, push the diff into
the max_heap(priority queue), and attempt to reach the next building using
bricks first. Bricks need to be subtracted by diff.

When bricks < 0, it means there are not enough bricks to run from the i-th
building to the (i+1)th building. At this point, we can try to use a ladder to
replace the maximum bricks between the previous two buildings, which is
the root of max_heap. Therefore, bricks can be incremented
by removing the root element of max_heap(Need to adjust the max_heap), and
decrease the number of ladders by 1.

When ladders == 0, we cannot perform the above actions for current building,
return (`current` - 1).


Time: O(n)
Space: O(n)
***/

typedef struct {
    int* arr;
    int cur_sz;
    int sz;
} heap_t;

static inline heap_t* heap_init(int sz) {
    heap_t* obj = malloc(sizeof(heap_t));
    obj->arr = malloc(sizeof(int) * sz);
    obj->cur_sz = 0;
    obj->sz = sz;
    return obj;
}

static inline void heap_dinit(heap_t* obj) {
    free(obj->arr);
    free(obj);
}

static inline void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
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

static int heap_pop(heap_t* obj) {
    int ret = obj->arr[0];
    obj->arr[0] = obj->arr[obj->cur_sz - 1];
    obj->cur_sz -= 1;
    max_heapify(obj->arr, 0, obj->sz);
    return ret;
}

static void heap_push(heap_t* obj, int val) {
    obj->arr[obj->cur_sz] = val;
    max_heapify_bottom_up(obj->arr, obj->cur_sz);
    obj->cur_sz += 1;
}

int furthestBuilding(int* heights, int heightsSize, int bricks, int ladders) {
    int ret = 0;
    heap_t* heap = heap_init(heightsSize);
    for (int i = 1; i < heightsSize; i++) {
        int diff = heights[i] - heights[i - 1];
        if (diff > 0) {
            bricks -= diff;
            heap_push(heap, diff);
            if (bricks < 0) {
                if (0 == ladders) {
                    heap_dinit(heap);
                    return i - 1;
                }
                bricks += heap_pop(heap);
                ladders--;
            }
        }
    }
    heap_dinit(heap);
    return heightsSize - 1;
}
