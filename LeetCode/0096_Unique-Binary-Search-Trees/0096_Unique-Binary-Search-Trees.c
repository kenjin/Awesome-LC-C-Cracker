/**

96. Unique Binary Search Trees [M]
Ref: https://leetcode.com/problems/unique-binary-search-trees/

Given n, how many structurally unique BST's (binary search trees) that
store values 1 ... n?

 */

int numTrees(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    
    int ret = 0, midCtr = 0;
    for (int i = 0; i < n/2 ; i++)
    {
        ret += (numTrees(i)*numTrees(n-i-1));
    }
    if (n % 2 != 0) /* odd case, handle root in the middle */
    {
        int halfCtr = numTrees((n+1)/2 - 1); /* Calculate half ctr */
        midCtr = halfCtr*halfCtr; /* leftCtr * rightCtr */
    }

    return (ret*2 + midCtr);
}

