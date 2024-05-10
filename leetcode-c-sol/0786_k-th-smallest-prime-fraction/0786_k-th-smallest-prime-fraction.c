
typedef struct {
    double value;
    int first;
    int second;
} pair;

typedef struct {
    pair *pairs;
    int capacity;
    int size;
} priority_q;

// Initialize min heap
static priority_q* create_priority_q(int capacity)
{
    priority_q *pq = (priority_q*)malloc(sizeof(priority_q));
    pq->capacity = capacity;
    pq->size = 0;
    pq->pairs = (pair*)malloc(sizeof(pair) * capacity);
    return pq;
}

// Insert element into min heap
static void push(priority_q *pq, double value, int first, int second)
{
    if (pq->size == pq->capacity) return;
    pair p = {value, first, second};
    pq->pairs[pq->size++] = p;
    int idx = pq->size - 1;
    while (idx > 0) {
        int parent = (idx - 1) >> 1;
        if (pq->pairs[idx].value < pq->pairs[parent].value) {
            pair temp = pq->pairs[idx];
            pq->pairs[idx] = pq->pairs[parent];
            pq->pairs[parent] = temp;
            idx = parent;
        } else {
            break;
        }
    }
}

// Extract the minimum element from min heap
pair pop(priority_q *pq) {
    if (pq->size == 0) {
        pair p = {-1.0 * INT_MAX, -1, -1};
        return p;
    }
    pair min_pair = pq->pairs[0];
    pq->pairs[0] = pq->pairs[pq->size - 1];
    pq->size--;
    int idx = 0;
    while ((idx << 1) + 1 < pq->size) {
        int left = (idx << 1) + 1;
        int right = (idx << 1) + 2;
        int min_idx = left;
        if (right < pq->size && pq->pairs[right].value < pq->pairs[left].value)
            min_idx = right;
        if (pq->pairs[idx].value <= pq->pairs[min_idx].value)
            break;

        pair temp = pq->pairs[idx];
        pq->pairs[idx] = pq->pairs[min_idx];
        pq->pairs[min_idx] = temp;
        idx = min_idx;
    }
    return min_pair;
}

int* kthSmallestPrimeFraction(int* A, int ASize, int K, int* returnSize) {
    // Create min heap
    priority_q *pq = create_priority_q(ASize * ASize);
    for (int i = 0; i < ASize; ++i)
        push(pq, 1.0 * A[i] / A[ASize - 1], i, ASize - 1);

    // Select the Kth smallest element
    while (--K) {
        pair t = pop(pq);
        t.second--;
        if (t.second > t.first)
            push(pq, 1.0 * A[t.first] / A[t.second], t.first, t.second);
    }
    // Extract the result
    pair result = pop(pq);
    int *res = (int *)malloc(sizeof(int) * 2);
    res[0] = A[result.first];
    res[1] = A[result.second];
    *returnSize = 2;
    free(pq->pairs);
    free(pq);
    return res;
}
