/**

779. K-th Symbol in Grammar [M]
Ref: https://leetcode.com/problems/k-th-symbol-in-grammar/

 */

/*
 * N=1               0
 * N=2          0         1
 * N=3       0    1     1    0
 * N=4      0 1  1 0   1 0  0 1
 *
 *-------------------------------
 *        0
 *      /   \
 *     0     1
 *   (odd)  (even)
 *  
 * -  odd child = parent
 * - even child = parent ^ 1
 *
 */
int kthGrammar(int N, int K)
{
    if (N == 1)
    {
        return 0;
    }   
    int parent = kthGrammar(N-1, (K+1)/2);
    return ((K & 0x1) ? parent : (parent^1));
}
