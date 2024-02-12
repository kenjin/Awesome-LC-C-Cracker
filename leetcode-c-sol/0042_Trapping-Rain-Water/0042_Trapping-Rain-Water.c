typedef struct {
    int ctr;
    int* arr;
} stack_t;

#define stack_init(SIZE)                                                       \
    { .ctr = 0, .arr = malloc(sizeof(int) * SIZE) }
#define stack_dinit(S)                                                         \
    do {                                                                       \
        free(S.arr);                                                           \
    } while (0)
#define stack_push(S, IDX)                                                     \
    do {                                                                       \
        S.arr[S.ctr++] = IDX;                                                  \
    } while (0)
#define stack_pop(S) (S.arr[--S.ctr])
#define stack_top(S) (S.arr[S.ctr - 1])
#define stack_is_empty(S) (S.ctr == 0 ? true : false)

#define MIN(a, b) (a < b ? a : b)

int trap(int* height, int heightSize)
{
    stack_t s = stack_init(heightSize);
    int ret = 0;
    for (int i = 0; i < heightSize; i++) {
        int height_r = height[i];
        if (!stack_is_empty(s) && height[stack_top(s)] <= height_r) {
            int valley_idx = stack_pop(s);
            /* - If there is only one height, it cannot form a pit, so skip it.
             * - If there is more than one height, we pop the top element of the
             *    stack and consider it as the pit. The new top element becomes 
             *    left boundary, and current height becomes right boundary. Then
             *    calculate the water volume by taking the minimum of the two 
             *    heights, subtracting the height of the pit, and multiplying by
             *    the diff between right boundary idx and left boundary idx
             *    minus 1.
             */
            while (!stack_is_empty(s)) {
                int tmp_idx = stack_pop(s);
                int tmp_h = MIN(height_r, height[tmp_idx]) - height[valley_idx];
                ret += (tmp_h * (i - tmp_idx - 1));
                if (height[tmp_idx] > height_r) {
                    stack_push(s, tmp_idx);
                    break;
                }
                valley_idx = tmp_idx;
            }
        }
        /* if the stack is empty or the current height is less than or equal to
         * the height at the top of the stack, push the idx of the 
         * current height onto the stack.
         */
        stack_push(s, i);
    }
    stack_dinit(s);
    return ret;
}
