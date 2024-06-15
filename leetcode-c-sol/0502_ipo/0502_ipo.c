#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int capital;
    int profit;
} proj_t;

typedef struct {
    proj_t* data;
    int size;
    int capacity;
} heap_t;

#define MAX_HEAP_POP(HEAP) __heap_pop(HEAP, true)
#define MIN_HEAP_POP(HEAP) __heap_pop(HEAP, false)
#define MAX_HEAP_PUSH(HEAP, ITEM) __heap_push(HEAP, ITEM, true)
#define MIN_HEAP_PUSH(HEAP, ITEM) __heap_push(HEAP, ITEM, false)

static inline void swap(proj_t* a, proj_t* b) {
    proj_t tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline int min_heap_top_capital(heap_t* heap) {
    if (heap->size > 0)
        return heap->data[0].capital;

    return -1;
}

static void __heap_push(heap_t* heap, proj_t item, bool is_max) {
    if (heap->size >= heap->capacity) {
        heap->capacity <<= 1;
        heap->data = realloc(heap->data, heap->capacity * sizeof(proj_t));
    }

    heap->data[heap->size] = item;
    int i = heap->size++;
    while (i > 0 && ((is_max && heap->data[i].profit > heap->data[(i - 1) >> 1].profit) ||
                     (!is_max && heap->data[i].capital < heap->data[(i - 1) >> 1].capital))) {
        swap(&heap->data[i], &heap->data[(i - 1) >> 1]);
        i = (i - 1) >> 1;
    }
}

static proj_t __heap_pop(heap_t* heap, bool is_max) {
    proj_t result = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    int i = 0;
    while (1) {
        int target = i;
        int left = (i << 1) + 1;
        int right = (i << 1) + 2;
        if (left < heap->size && ((is_max && heap->data[left].profit > heap->data[target].profit) ||
                                  (!is_max && heap->data[left].capital < heap->data[target].capital)))
            target = left;

        if (right < heap->size && ((is_max && heap->data[right].profit > heap->data[target].profit) ||
                                   (!is_max && heap->data[right].capital < heap->data[target].capital)))
            target = right;

        if (target == i)
            break;

        swap(&heap->data[i], &heap->data[target]);
        i = target;
    }
    return result;
}

int findMaximizedCapital(int k, int w, int* profits, int profits_size,
                         int* capital, int capital_size) {
    heap_t min_heap = {malloc(capital_size * sizeof(proj_t)), 0, capital_size};
    heap_t max_heap = {malloc(capital_size * sizeof(proj_t)), 0, capital_size};

    for (int i = 0; i < capital_size; ++i) {
        proj_t proj = {capital[i], profits[i]};
        MIN_HEAP_PUSH(&min_heap, proj);
    }

    for (int i = 0; i < k; i++) {
        while (min_heap.size > 0 && min_heap_top_capital(&min_heap) <= w) {
            proj_t proj = MIN_HEAP_POP(&min_heap);
            MAX_HEAP_PUSH(&max_heap, proj);
        }

        if (!max_heap.size)
            break;

        proj_t proj = MAX_HEAP_POP(&max_heap);
        w += proj.profit;
    }

    free(min_heap.data);
    free(max_heap.data);
    return w;
}

