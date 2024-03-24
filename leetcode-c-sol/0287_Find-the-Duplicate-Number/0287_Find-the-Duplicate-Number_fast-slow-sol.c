int findDuplicate(int* nums, int numsSize) 
{
    int slow = 0, fast = 0;
    while (1) {
        slow = nums[slow];
        fast = nums[nums[fast]];
        if (slow == fast)
            break;
    }

    int idx = 0;
    while (1) {
        slow = nums[slow];
        idx = nums[idx];
        if (slow == idx)
            break;
    }
    return slow;
}
