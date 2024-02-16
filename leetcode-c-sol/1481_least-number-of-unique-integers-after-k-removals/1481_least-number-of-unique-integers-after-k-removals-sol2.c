// Greedy: Delete from the least quantity
// - The original idea was to use a hash table to store the frequency of each
//   number.
// - A better approach is to sort the array first, and then count the
//   frequencies of each number.

static int compare(const void* a, const void* b) { return *(int*)a - *(int*)b; }

int findLeastNumOfUniqueInts(int* arr, int arrSize, int k) {
    int ctr[arrSize], ctr_idx = 0;
    memset(ctr, 0, sizeof(int) * arrSize);
    // sort at first
    qsort(arr, arrSize, sizeof(int), compare);

    ctr[0] = 1;
    for (int i = 1; i < arrSize; i++) {
        if (arr[i] != arr[i - 1])
            ctr_idx++;
        ctr[ctr_idx]++;
    }

    int ret = ctr_idx + 1;
    // sort by freq
    qsort(ctr, ret, sizeof(int), compare);

    for (ctr_idx = 0; k > 0; k--) {
        ctr[ctr_idx]--;
        if (ctr[ctr_idx] == 0) {
            ctr_idx++;
            ret--;
        }
    }

    return ret;
}
