bool uniqueOccurrences(int* arr, int arrSize)
{
    //-1000 <= arr[i] <= 1000
    int freq[2001] = {0};
    for (int i = 0; i < arrSize; i++) {
        freq[arr[i]+1000]++;
    }

    int dup[1001] = {0};
    for (int i = 0; i < 2001; i++) {
        if (freq[i])
            dup[freq[i]]++;
    }

    for (int i = 0; i < 1001; i++) {
        if (dup[i] > 1)
            return false;
    }

    return true;
}
