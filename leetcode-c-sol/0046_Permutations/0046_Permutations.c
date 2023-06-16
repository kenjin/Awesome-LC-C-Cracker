/**
46. Permutations [M]

Given a collection of distinct integers, return all possible permutations.

Example:

Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

*/


void calPermute(int ***ret, int *returnSize, int *eachRes, int *nums, int numsSize, char *usedArr, int index)
{
    if (index == numsSize)
    {
        *returnSize += 1;
        int *tmp = malloc(sizeof(int)*numsSize);
        memcpy(tmp, eachRes, sizeof(int)*numsSize);
        (*ret)[(*returnSize)-1] = tmp;
        return ;
    }

    for (int i = 0; i < numsSize; i++)
    {
        if (usedArr[i])
        {
            continue;
        }
        eachRes[index] = nums[i];
        usedArr[i] = 1;
        calPermute(ret, returnSize, eachRes, nums, numsSize, usedArr, index+1);
        usedArr[i] = 0;
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int** permute(int* nums, int numsSize, int* returnSize) {

    if (numsSize == 0)
    {
        return NULL;
    }

    int totalPer = numsSize;
    for (int i = 2; i < numsSize; i++)
    {
        totalPer *= i;
    }

    int **ret = (int **)malloc(sizeof(int *)*(totalPer));
    int *eachRes = (int*)malloc(sizeof(int) * numsSize);
    char *usedArr = (char*)calloc(numsSize, sizeof(char));
     *returnSize = 0;
    calPermute(&ret, returnSize, eachRes, nums, numsSize, usedArr, 0 /* index */);

    free(eachRes);
    free(usedArr);
    return ret;
}

