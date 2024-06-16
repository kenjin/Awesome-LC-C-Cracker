
/***

- The loop runs as long as `miss` is less than or equal to n.
- If the current element in nums (pointed to by i) is less than or equal to 
  miss, it means we can use this element to cover more numbers. So, we add 
  nums[i] to miss and move to the next element. 
- If the current element is greater than miss, it means we need to add a patch
  (which will be miss itself) to cover the gap. We then double miss to reflect 
  that we have added a new element and increment the patch count res.

***/

int minPatches(int* nums, int nums_size, int n) {
    long miss =
        1; // used to track the smallest number that cannot be formed using the
           // sum of elements in nums and the patches added so far.
    int res = 0, i = 0;

    while (miss <= n) {
        if (i < nums_size && nums[i] <= miss) {
            miss += nums[i++];
        } else {
            miss += miss;
            res++;
        }
    }

    return res;
}
