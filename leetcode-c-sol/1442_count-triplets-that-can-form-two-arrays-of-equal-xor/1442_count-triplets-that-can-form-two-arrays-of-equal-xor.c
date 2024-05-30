/***

Approach: bitwise operation

Since both a and b are results of bitwise operations, and a == b, we can
conclude that a ^ b = 0 based on the properties of XOR, because two identical
numbers XORed together equal 0. This conclusion can be reversed. Therefore, this
problem is about finding whether there exists a triplet that satisfies a ^ b =
0. Additionally, since a and b are formed by XORing multiple bits, and XOR
operation is associative, for example, (a ^ b) ^ c = a ^ (b ^ c), once we find a
segment from index a to c whose XOR result is 0, the position of b in between
can be arbitrary. Thus, there are c - a possible positions for b.

***/

int countTriplets(int* arr, int arrSize) {
    int ret = 0;
    for (int a = 0; a < arrSize - 1; a++) {
        int tmp = arr[a];
        for (int c = a + 1; c < arrSize; c++) {
            tmp ^= arr[c];
            if (!tmp)
                ret += (c - a);
        }
    }
    return ret;
}
