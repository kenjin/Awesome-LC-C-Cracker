
int singleNumber(int *nums, int numsSize)
{
    int n1 = 0, n2 = 0, n3 = 0;
    for (int i = 0; i < numsSize; i++) {
        n2 |= n1 & nums[i];
        n1 ^= nums[i];
        n3 = n1 & n2;
        n1 &= ~n3;
        n2 &= ~n3;
    }

    return n1;
}
