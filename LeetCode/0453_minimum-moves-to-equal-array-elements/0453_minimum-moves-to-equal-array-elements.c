#define MIN(a, b) (a < b ? a : b)

int minMoves(int* nums, int numsSize)
{
    int min = INT_MAX;
    int moves = 0;
    
    for (int x = 0; x < numsSize; x++)
    {
        min = MIN(min, nums[x]);
    }
    
    for (int x = 0; x < numsSize; x++)
    {
        moves += nums[x] - min;
    }

    return moves;
}

