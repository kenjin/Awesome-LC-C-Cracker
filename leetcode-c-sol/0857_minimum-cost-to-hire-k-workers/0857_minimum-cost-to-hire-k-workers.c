#include <float.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
    double ratio;
    int quality;
} worker_t;

typedef struct {
    int *arr;
    int capacity;
    int size;
} pq_t;

pq_t* create_pq(int capacity)
{
    pq_t *pq = (pq_t *)malloc(sizeof(pq_t));
    pq->capacity = capacity;
    pq->size = 0;
    pq->arr = malloc(sizeof(int) * capacity);
    return pq;
}

static inline void destroy_pq(pq_t *pq)
{
    free(pq->arr);
    free(pq);
}

static void push(pq_t *pq, int value)
{
    if (pq->size == pq->capacity)
        return;

    pq->arr[pq->size++] = value;
    int idx = pq->size - 1;
    while (idx > 0) {
        int parent = (idx - 1) >> 1;
        if (pq->arr[idx] > pq->arr[parent]) {
            int tmp = pq->arr[idx];
            pq->arr[idx] = pq->arr[parent];
            pq->arr[parent] = tmp;
            idx = parent;
        } else {
            break;
        }
    }
}

static int pop(pq_t *pq)
{
    int ret = pq->arr[0];
    pq->arr[0] = pq->arr[pq->size - 1];
    pq->size--;
    int idx = 0;
    while ((idx << 1) + 1 < pq->size) {
        int left = (idx << 1) + 1;
        int right = (idx << 1) + 2;
        int max_idx = left;
        if (right < pq->size && pq->arr[right] > pq->arr[left])
            max_idx = right;
        if (pq->arr[idx] >= pq->arr[max_idx])
            break;

        int tmp = pq->arr[idx];
        pq->arr[idx] = pq->arr[max_idx];
        pq->arr[max_idx] = tmp;
        idx = max_idx;
    }
    return ret;
}

int compare(const void* a, const void* b)
{
    return (((worker_t *)a)->ratio > ((worker_t *)b)->ratio) ? 1 : -1;
}

double mincostToHireWorkers(int* quality, int qualitySize, int* wage, int wageSize, int K)
{
    double res = DBL_MAX, qsum = 0;
    worker_t *workers = (struct Worker*)malloc(qualitySize * sizeof(worker_t));
    pq_t *pq = create_pq(qualitySize);

    for (int i = 0; i < qualitySize; ++i) {
        workers[i].ratio = (double)wage[i] / quality[i];
        workers[i].quality = quality[i];
    }

    qsort(workers, qualitySize, sizeof(worker_t), compare);

    for (int i = 0; i < qualitySize; ++i) {
        qsum += workers[i].quality;
        push(pq, workers[i].quality);
        if (pq->size > K)
            qsum -= pop(pq);
        if (pq->size == K)
            res = min(res, qsum * workers[i].ratio);
    }

    free(workers);
    destroy_pq(pq);
    return res;
}
