/***
Approach: Greedy

To obtain the optimal solution, consume less power as much as possible to gain a
point (face-up), and consume a point to gain more power (face-down) whenever
possible.
- Thus, first sort the tokens from smallest to largest, using head and tail
  pointers.
- Perform face-up to gain score from the head.
- If power is insufficient, perform face-down to obtain power from the tail.
- Since it's possible to do nothing, if there's only one token left and power is
  insufficient, don't consume more score to gain power.

Time: O(n)
Space: O(1)
***/

static int cmp(const void* a, const void* b) { return *(int*)a - *(int*)b; }

int bagOfTokensScore(int* tokens, int tokensSize, int power) {
    qsort(tokens, tokensSize, sizeof(int), cmp);
    int head = 0, tail = tokensSize - 1, score = 0;
    while (head <= tail) {
        if (power >= tokens[head]) {
            // Have extra power to gain score
            power -= tokens[head++];
            score++;
        } else if (score > 0 && head != tail) {
            // Have extra score and ensure it's not the last token
            power += tokens[tail--];
            score--;
        } else {
            // Not enough power and enough score
            break;
        }
    }

    return score;
}

