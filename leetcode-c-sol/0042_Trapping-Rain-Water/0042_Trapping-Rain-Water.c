typedef struct {
    int size;
    int cur;
    int *arr;
} stack_t;

#define stack_create(SIZE) {.size = SIZE, .cur = -1, .arr = malloc(sizeof(int) * SIZE)}
#define stack_free(S)      do {free(S.arr);} while(0)
#define stack_push(S, IDX) do {S.arr[++S.cur] = IDX;} while (0)
#define stack_pop(S)       (S.arr[S.cur--])
#define stack_top(S)       (S.arr[S.cur])
#define stack_is_empty(S)  (S.cur == -1 ? true : false)
#define MIN(A, B) (A < B ? A : B)

int trap(int* height, int heightSize)
{
    int ret = 0;
    stack_t s = stack_create(heightSize);
    for (int i = 0; i < heightSize; i++) {
        int right_h = height[i];
        if (stack_is_empty(s) && right_h == 0)
            continue;

        if (!stack_is_empty(s) && 
                height[stack_top(s)] <= right_h) {
            int valley_idx = stack_pop(s);
            while (!stack_is_empty(s)) {
                int tmp_idx = stack_pop(s);
                int tmp_h = (MIN(right_h, height[tmp_idx]) - height[valley_idx]);
                ret += (tmp_h * (i - tmp_idx - 1));
                // Pop until find the higher one, push it back to keep monotonic stack
                if (height[tmp_idx] > right_h) {
                    stack_push(s, tmp_idx);
                    break;
                }
                valley_idx = tmp_idx;
            }
        }
        stack_push(s, i);
    }
    stack_free(s);
    return ret;
}
