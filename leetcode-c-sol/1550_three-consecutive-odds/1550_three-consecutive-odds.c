bool threeConsecutiveOdds(int* arr, int arrSize) {
    int odd_ctr = 0;
    for (int i = 0; i < arrSize; i++) {
        if (arr[i] & 0x1)
            odd_ctr++;
        else
            odd_ctr = 0;
        if (odd_ctr == 3)
            return true;
    }

    return false;
}
