int specialArray(int* nums, int numsSize) {
    int l = 0, r = numsSize;
    while (l <= r) {
        int mid = l + ((r - l) >> 1), ctr = 0;
        for (int i = 0; i < numsSize; i++) {
            if (nums[i] >= mid)
                ctr++;
        }

        if (ctr == mid)
            return mid;
        else if (ctr < mid)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}
