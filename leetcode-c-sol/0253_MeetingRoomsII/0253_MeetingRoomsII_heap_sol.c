
#define XOR_SWAP(A, B)  \
    do { if (A != B) {A = A ^ B; B = A ^ B; A = A ^ B;}} while (0);  

typedef struct {
    int *p;
    int cur_sz;
} minheap_t;

int compare(const void *a, const void *b)
{
    return (*(int **)a)[0] < (*(int **)b)[0] ? -1 : 1;
}

void heapify_bottom_up(int *p, int cur)
{
    int p_idx;
    while (cur > 0) {
        p_idx = ((cur-1) >> 1);
        if (p[p_idx] <= p[cur])
            break;
        XOR_SWAP(p[p_idx], p[cur]);
        cur = p_idx;
    } 
}

void heapify_sift_down(int *p, int head, int size)
{
    int lchild = (head << 1) +1;
    int rchild = (head << 1) +2;
    int min = head;
    if (lchild < size && p[lchild] < p[min]) 
        min = lchild;
    if (rchild < size && p[rchild] < p[min]) 
        min = rchild;

    if (min != head) {
        XOR_SWAP(p[min], p[head]);
        heapify_sift_down(p, min, size);
    }
}

int minMeetingRooms(int **intervals, int intervalsSize, int *intervalsColSize)
{
    qsort(intervals, intervalsSize, sizeof(int *), compare);

    minheap_t h = {.cur_sz = 0, .p = malloc(sizeof(int)*intervalsSize)};
    for (int i = 0; i < intervalsSize; i++) {
        if (h.cur_sz != 0 && h.p[0] <= intervals[i][0]) {
            // Replace new root
            h.p[0] = intervals[i][1];
            heapify_sift_down(h.p, 0, h.cur_sz);
        } else {
            h.p[h.cur_sz] = intervals[i][1];
            heapify_bottom_up(h.p, h.cur_sz);
            h.cur_sz++;
        }
    }
    free(h.p);
    return h.cur_sz;
}
