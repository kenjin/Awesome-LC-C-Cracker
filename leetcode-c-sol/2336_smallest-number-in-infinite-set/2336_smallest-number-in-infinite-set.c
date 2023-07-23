
#define MAX_OP_CNT 1000
#define MAX_SZ (MAX_OP_CNT >> 1)

#define XOR_SWAP(a, b) do { \
    a = a ^ b; b = a ^ b; a = a ^ b; \
} while (0)


typedef struct {
    unsigned short pop_ctr;
    unsigned short heap[MAX_SZ];
    unsigned short heap_sz;
    char heap_map[MAX_SZ + 1]; // Just plus one more size to represent 1 to MAX_SZ in hash map
} SmallestInfiniteSet;

static void heapify(unsigned short *heap, unsigned short cur, unsigned short size)
{
    unsigned short l_chd = (cur << 1) + 1, r_chd = (cur << 1) + 2, min = cur;
    if (l_chd < size && heap[l_chd] < heap[min])
        min = l_chd;
    if (r_chd < size && heap[r_chd] < heap[min])
        min = r_chd;

    if (min != cur) {
        XOR_SWAP(heap[min], heap[cur]);
        heapify(heap, min, size);
    }
}

static void add_min_heap(unsigned short *heap, unsigned short heap_sz, unsigned short add_num)
{
    heap[heap_sz] = add_num;
    for (int i = heap_sz; i > 0;) {
        int parent_idx = ((i - 1) >> 1);
        if (heap[i] < heap[parent_idx]) {
            XOR_SWAP(heap[i], heap[parent_idx]);
            i = parent_idx;
        }
        else {
            break;
        }
    }
}

static int del_min_heap(unsigned short *heap, unsigned short size)
{
    unsigned short ret = heap[0];
    heap[0] = heap[size - 1];
    heapify(heap, 0, size);
    return (int)ret;
}

SmallestInfiniteSet* smallestInfiniteSetCreate()
{
    SmallestInfiniteSet *sis_ctx = calloc(1, sizeof(SmallestInfiniteSet));
    sis_ctx->pop_ctr = 1;
    return sis_ctx;
}

int smallestInfiniteSetPopSmallest(SmallestInfiniteSet* obj) {
    int ret;
    if (obj->heap_sz > 0 && obj->heap[0] < obj->pop_ctr) {
        ret = del_min_heap(obj->heap, obj->heap_sz);
        obj->heap_sz -= 1;
        obj->heap_map[ret] = 0;
    } else {
        ret = obj->pop_ctr;
        obj->pop_ctr += 1;
    }

    return ret;
}

void smallestInfiniteSetAddBack(SmallestInfiniteSet* obj, int num) {
    // Add to min-heap   
    if (num < obj->pop_ctr && obj->heap_map[num] == 0) {
        add_min_heap(obj->heap, obj->heap_sz, (unsigned short)num);
        obj->heap_sz += 1;
        obj->heap_map[num] = 1;
    }
}

void smallestInfiniteSetFree(SmallestInfiniteSet* obj) {
    free(obj);
}

/**
 * Your SmallestInfiniteSet struct will be instantiated and called as such:
 * SmallestInfiniteSet* obj = smallestInfiniteSetCreate();
 * int param_1 = smallestInfiniteSetPopSmallest(obj);

 * smallestInfiniteSetAddBack(obj, num);

 * smallestInfiniteSetFree(obj);
 */
