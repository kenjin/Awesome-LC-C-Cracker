
int singleNumber(int* nums, int numsSize)
{
    int ret = 0;
    for (int x = 0; x < numsSize; x++)
    {
        ret = ret^nums[x];
    }   
    return ret;
}
