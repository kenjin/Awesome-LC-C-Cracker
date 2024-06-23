/***

Approach: Sliding Window + Monotonic Queue

Maintain a monotonically decreasing queue, maxq, and a monotonically increasing
queue, minq, where both store indices. The front element of maxq is the index of
the current maximum element, and the front element of minq is the index of the
current minimum element. Note that while storing elements is possible, storing
indices is beneficial because it remains unaffected by duplicate elements.

Also, need two pointers, left and i. Initially, i moves forward. When it finds
that:
- maxq is not empty and the last element in maxq is smaller than the current
  element nums[i], it continually polls elements from maxq until it becomes
  monotonically decreasing again.
- minq is not empty and the last element in minq is larger than the current
  element nums[i], it continually polls elements from minq until it becomes
  monotonically increasing again.

At this point, we check: if both queues are not empty, but the diff between
the front elements in the two queues (one being the maximum value and the other
the minimum value) is greater than the limit, we start moving the left pointer
to the right. As we move the left pointer, if any element in the queues has an 
index less than or equal to left, we poll it out because it's no longer needed.
Here, storing indices is advantageous because the indices are sequentially
added to both queues, so if the diff exceeds the limit, we need to start 
checking from the very beginning of the left pointer.

Time complexity: O(n)
Space complexity: O(n)

***/

// Node for deque
typedef struct node {
    int value;
    struct node* next;
    struct node* prev;
} node_t;

// Deque structure
typedef struct deque {
    node_t* front;
    node_t* rear;
    int sz;
} deque_t;

static deque_t* create_deque() {
    deque_t* deque = (deque_t*)malloc(sizeof(deque_t));
    deque->front = deque->rear = NULL;
    deque->sz = 0;
    return deque;
}

static void add_rear(deque_t* deque, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = deque->rear;
    if (deque->rear)
        deque->rear->next = new_node;
    else
        deque->front = new_node;
    deque->rear = new_node;
    deque->sz++;
}

static int rm_front(deque_t* deque) {
    if (deque->front == NULL)
        return -1;
    node_t* tmp = deque->front;
    int value = tmp->value;
    deque->front = deque->front->next;
    if (deque->front)
        deque->front->prev = NULL;
    else
        deque->rear = NULL;
    free(tmp);
    deque->sz--;
    return value;
}

static int rm_rear(deque_t* deque) {
    if (deque->rear == NULL)
        return -1;
    node_t* tmp = deque->rear;
    int value = tmp->value;
    deque->rear = deque->rear->prev;
    if (deque->rear)
        deque->rear->next = NULL;
    else
        deque->front = NULL;
    free(tmp);
    deque->sz--;
    return value;
}

static inline int get_front(deque_t* deque) {
    return deque->front ? deque->front->value : -1;
}

static inline int get_rear(deque_t* deque) {
    return deque->rear ? deque->rear->value : -1;
}

static inline int is_empty(deque_t* deque) {
    return deque->sz == 0;
}

static inline void free_deque(deque_t* deque) {
    while (!is_empty(deque))
        rm_front(deque);
    free(deque);
}

int longestSubarray(int* nums, int nums_sz, int limit) {
    deque_t *maxq = create_deque(), *minq = create_deque();
    int left = 0, n = nums_sz;

    for (int i = 0; i < n; i++) {
        int v = nums[i];
        // Maintain maxq as decreasing
        while (!is_empty(maxq) && get_rear(maxq) < v)
            rm_rear(maxq);
        // Maintain minq as increasing
        while (!is_empty(minq) && get_rear(minq) > v)
            rm_rear(minq);
        add_rear(maxq, v);
        add_rear(minq, v);

        // Check if current window is valid
        if (get_front(maxq) - get_front(minq) > limit) {
            if (get_front(maxq) == nums[left])
                rm_front(maxq);
            if (get_front(minq) == nums[left])
                rm_front(minq);
            left++;
        }
    }
    
    int result = n - left;
    free_deque(maxq);
    free_deque(minq);
    return result;
}
