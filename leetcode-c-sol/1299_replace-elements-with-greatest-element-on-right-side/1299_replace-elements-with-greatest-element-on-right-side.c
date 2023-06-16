
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *replaceElements(int *arr, int arrSize, int *returnSize)
{
    *returnSize = arrSize;
    int max = arr[arrSize - 1];
    arr[arrSize - 1] = -1;
    for (int i = arrSize - 2; i >= 0; i--) {
        int tmp = max;
        max = (max > arr[i] ? max : arr[i]);
        arr[i] = tmp;
    }

    return arr;
}