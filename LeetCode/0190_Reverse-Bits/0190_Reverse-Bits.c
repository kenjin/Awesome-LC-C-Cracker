/**

190. Reverse Bits [E]
Ref: https://leetcode.com/problems/reverse-bits/

 */

uint32_t reverseBits(uint32_t n)
{
    uint32_t ret = 0;
    for (int x = 0; x < 32; x++)
    {
        ret = ret << 1;
        ret = ret | ((n >> x) & 0x1);
    }
    return ret;
}
