static inline void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void min_heapify(int *nums, int cur, int size)
{
    int l_chd = (cur << 1) + 1;
    int r_chd = (cur << 1) + 2;
    int min = cur;
    if (l_chd < size && nums[l_chd] < nums[min])
        min = l_chd;
    if (r_chd < size && nums[r_chd] < nums[min])
        min = r_chd;

    if (min != cur) {
        swap(&nums[min], &nums[cur]);
        min_heapify(nums, min, size);
    }
}

static void min_heapify_bottom_up(int *n, int i) {
    // Find parent 
    int parent = ((i - 1) >> 1);
    if (parent >= 0) { 
        // For Max-Heap 
        // If current node is greater than its parent 
        // Swap both of them and call heapify again 
        // for the parent 
        if (n[i] < n[parent]) { 
            swap(&n[i], &n[parent]); 
            // Recursively heapify the parent node 
            min_heapify_bottom_up(n, parent); 
        } 
    } 
}

static inline void add_min_heap(int *n, int num, int *size)
{
    n[*size] = num;
    *size += 1;
    min_heapify_bottom_up(n, *size - 1);
}

static int del_min_heap(int *n, int *size)
{
    int ret = n[0];
    n[0] = n[*size-1];
    *size -= 1;
    min_heapify(n, 0, *size);
    return ret;
}

static void max_heapify(int *nums, int cur, int size)
{
    int l_chd = (cur << 1) + 1;
    int r_chd = (cur << 1) + 2;
    int max = cur;
    if (l_chd < size && nums[l_chd] > nums[max])
        max = l_chd;
    if (r_chd < size && nums[r_chd] > nums[max])
        max = r_chd;

    if (max != cur) {
        swap(&nums[max], &nums[cur]);
        max_heapify(nums, max, size);
    }
}

void max_heapify_bottom_up(int *n, int i) {
    // Find parent 
    int parent = ((i - 1) >> 1);
    if (parent >= 0) {
        if (n[i] > n[parent]) { 
            swap(&n[i], &n[parent]);
            max_heapify_bottom_up(n, parent); 
        } 
    } 
}

static inline void add_max_heap(int *n, int num, int *size)
{
    n[*size] = num;
    *size += 1;
    max_heapify_bottom_up(n, *size - 1);
}

static int del_max_heap(int *n, int *size)
{
    int ret = n[0];
    n[0] = n[*size-1];
    *size -= 1;
    max_heapify(n, 0, *size);
    return ret;
}



typedef struct {
    int *l_maxheap;
    int *r_minheap;
    int l_ctr;
    int r_ctr;
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder *obj = malloc(sizeof(MedianFinder));
    obj->l_maxheap = malloc(sizeof(int)*50000);
    obj->r_minheap = malloc(sizeof(int)*50000);
    obj->l_ctr= 0;
    obj->r_ctr= 0;
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num)
{
    // Add to left max heap
    add_max_heap(obj->l_maxheap, num, &obj->l_ctr);
    // Delete MAX from the left(maxheap)
    int tmp = del_max_heap(obj->l_maxheap, &(obj->l_ctr));
    // Put to right min heap
    add_min_heap(obj->r_minheap, tmp, &obj->r_ctr);
    // Make sure size of max-heap is equal or larger than 1
    if (obj->l_ctr < obj->r_ctr) {
        int tmp = del_min_heap(obj->r_minheap, &(obj->r_ctr));
        add_max_heap(obj->l_maxheap, tmp, &obj->l_ctr);
    }
}

double medianFinderFindMedian(MedianFinder* obj)
{
    if (obj->l_ctr == obj->r_ctr) {
        return ((double)(obj->l_maxheap[0] + obj->r_minheap[0]) >> 1);
    } else {
        return obj->l_maxheap[0];
    }
}

void medianFinderFree(MedianFinder* obj)
{
    free(obj->l_maxheap);
    free(obj->r_minheap);
    free(obj);   
}
