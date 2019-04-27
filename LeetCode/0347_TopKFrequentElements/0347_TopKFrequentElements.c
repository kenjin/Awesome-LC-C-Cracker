/**

347. Top K Frequent Elements Medium

Given a non-empty array of integers, return the k most frequent elements.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
Note:

You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

 */


struct nums_freq
{
    int num;
    int ctr;
};

int compare(const void *p1, const void *p2)
{
    return *(int *)p1 - *(int *)p2;
}

int compareStruct(const void *p1, const void *p2)
{
    const struct nums_freq *sp1 = (const struct nums_freq *) p1;
    const struct nums_freq *sp2 = (const struct nums_freq *) p2;
    return (int)(sp1->ctr - sp2->ctr);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){

    if (numsSize == 0 || k == 0)
    {
        *returnSize = 0;
        return NULL;
    }

    qsort(nums, numsSize, sizeof(int), compare);
    /* init the first element */
    int currentIdx = 0;
    struct nums_freq freq[numsSize];
    memset(&freq, 0, sizeof(struct nums_freq)*numsSize);
    freq[currentIdx].num = nums[0];
    freq[currentIdx].ctr = 1;

    for (int i = 1; i < numsSize; i++)
    {
        if ((nums[i] != nums[i-1]))
        {
            currentIdx++;
            freq[currentIdx].num = nums[i];
            freq[currentIdx].ctr = 1;
        } else
        {
            freq[currentIdx].ctr++;
        }
    }

    int totalFreqIndex = currentIdx+1;
    qsort(freq, totalFreqIndex, sizeof(struct nums_freq), compareStruct);

    int *ret = malloc(sizeof(int)*k);
    for (int i = 0; i < k; i++)
    {
        int index = (totalFreqIndex-1)-i;
        ret[i] = freq[index].num;
    }
    *returnSize = k;

    return ret;
}

