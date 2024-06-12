
static inline void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sortColors(int* nums, int numsSize) {
    int cur_idx = 0, red_idx = 0, blue_idx = numsSize - 1;
    while (cur_idx <= blue_idx) {
        if (nums[cur_idx] == 2) {
            swap(&nums[cur_idx], &nums[blue_idx]);
            blue_idx--;
            continue;
        } else if (nums[cur_idx] == 0) {
            swap(&nums[cur_idx], &nums[red_idx]);
            red_idx++;
        }
        cur_idx++;
    }
}
