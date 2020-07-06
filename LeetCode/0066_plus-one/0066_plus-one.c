/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *plusOne(int *digits, int digitsSize, int *returnSize)
{
    int carry = 1;
    for (int i = digitsSize - 1; i >= 0; i--) {
        int tmp = digits[i];
        digits[i] = (tmp + carry) % 10;
        carry = (tmp + carry) / 10;
    }

    if (!carry) {
        *returnSize = digitsSize;
        return digits;
    }

    int *ret = (int *) malloc(sizeof(int) * (digitsSize + 1));
    ret[0] = 1;
    *returnSize = digitsSize + 1;
    memcpy(&ret[1], digits, sizeof(int) * digitsSize);
    return ret;
}
