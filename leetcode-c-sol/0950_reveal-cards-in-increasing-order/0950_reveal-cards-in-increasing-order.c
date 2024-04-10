static int cmp(const void* a, const void* b) { return *(int*)a - *(int*)b; }

int* deckRevealedIncreasing(int* deck, int deckSize, int* returnSize)
{
    // Sort the deck elements in ascending order.
    qsort(deck, deckSize, sizeof(int), cmp);

    // Create a simple queue to record the index order.
    // Initialize to sequentially put all deck indices into the queue.
    int* idx_q = malloc(sizeof(int) * deckSize);
    int front = 0, rear = 0;
    for (int i = 0; i < deckSize; i++)
        idx_q[i] = i;

    int* ret = malloc(sizeof(int) * deckSize);
    *returnSize = deckSize;

    // Handle two indices in one round, so process a total of `deckSize - 1`
    // elements in this loop.
    for (int deck_ctr = 0; deck_ctr < deckSize - 1; deck_ctr++) {
        // Dequeue to get the current index, then assign the latest deck element
        // to the corresponding `ret` position.
        ret[idx_q[front]] = deck[deck_ctr];
        front = (front + 1) % deckSize;
        // Dequeue to get the next index and then perform enqueue.
        idx_q[rear] = idx_q[front];
        front = (front + 1) % deckSize;
        rear = (rear + 1) % deckSize;
    }

    // Handle the last element from the queue.
    ret[idx_q[front]] = deck[deckSize - 1];
    free(idx_q);
    return ret;
}

