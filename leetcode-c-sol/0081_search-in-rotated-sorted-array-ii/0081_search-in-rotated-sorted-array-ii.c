
// Same as `33. Search in Rotated Sorted Array
// Only need to consider the case like [1, 1, 1, 0, 1]
//                                            M     T
int search(int* nums, int numsSize, int target)
{
    int head = 0, tail = numsSize - 1;

    while (head <= tail) {
        int mid = head + ((tail-head) >> 1);
        if (target == nums[mid])
            return true;

        if (nums[mid] < nums[tail]) {
            if (target > nums[mid] && target <= nums[tail])
                head = mid + 1;
            else
                tail = mid -1;

        } else if (nums[mid] == nums[tail]){
            tail--;
        } else {
            if (target >= nums[head] && target < nums[mid])
                tail = mid - 1;
            else
                head = mid + 1;
        }
    }
    return false;
}
