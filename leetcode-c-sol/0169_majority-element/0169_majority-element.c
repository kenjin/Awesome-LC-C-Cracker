int majorityElement(int* nums, int numsSize)
{
    int maj = nums[0], repeat = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == maj) {
            repeat++;
        } else {
            repeat--;
            if (repeat == 0) {
                maj = nums[i];
                repeat = 1;
            }
        }
    }
    return maj;
}
