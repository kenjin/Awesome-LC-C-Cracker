/***

The step-by-step approach:

- Initialize an array is_flipped of size n to keep track of whether each
  position has been flipped.
- Traverse the entire array A, maintaining a variable cur_flipped to represent
  the current number of flips within the sliding window.
- If i >= K, update cur_flipped by XOR-ing the flipped status of the current
  position with the status of the position K steps back.
- If (cur_flipped & 1) equal A[i], it means we need to flip current position.
  Set is_flipped[i] to 1, update cur_flipped by XOR-ing with 1, and increment 
  the result res.
- If i + K > n, it’s not possible to achieve the transformation, so return -1.

The final result is the value of res.

***/

int minKBitFlips(int* A, int ASize, int K) {
    int res = 0, cur_flipped = 0;
    char* is_flipped = (char*)calloc(ASize, sizeof(char));

    for (int i = 0; i < ASize; i++) {
        if (i >= K)
            cur_flipped ^= is_flipped[i - K];
        if ((cur_flipped & 0x1) == A[i]) {
            if (i + K > ASize) {
                free(is_flipped);
                return -1;
            }
            is_flipped[i] = 1;
            cur_flipped ^= 1;
            res++;
        }
    }

    free(is_flipped);
    return res;
}
