/***

Approach: Counting Sort

Counting Sort Concept: Uses the count array to record the occurrence count of
each element in arr1, which can be completed in O(n) time. Reconstructing
Partial Order: According to the order in arr2, the corresponding elements are
added to arr1 based on their occurrence count. This ensures that the relative
order in arr1 matches arr2. Handling Remaining Elements: Elements not present in
arr2 are appended to the end of arr1 in ascending order. This part uses simple
sequential traversal and appending operations.


Time Complexity: O(n + m + k), where n is the length of arr1, m is the length of
arr2, and k is the size of the count array (fixed at 1001 here).
Space Complexity: O(1), because the size of the count array is fixed and does 
not grow with input size.

***/

static int cmp(const void* a, const void* b) { return *(int*)a - *(int*)b; }

int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size,
                       int* returnSize) {
    int count[1001] = {0};
    // Record the occurrence count of each element in arr1
    for (int i = 0; i < arr1Size; i++)
        count[arr1[i]]++;

    int idx = 0;
    // Reconstruct part of arr1 based on the order in arr2
    for (int i = 0; i < arr2Size; i++) {
        while (count[arr2[i]] > 0) {
            arr1[idx++] = arr2[i];
            count[arr2[i]]--;
        }
    }
    // Append the remaining elements to the rest of arr1
    for (int i = 0; i < 1001; i++) {
        while (count[i] > 0) {
            arr1[idx++] = i;
            count[i]--;
        }
    }

    *returnSize = arr1Size;
    return arr1;
}

