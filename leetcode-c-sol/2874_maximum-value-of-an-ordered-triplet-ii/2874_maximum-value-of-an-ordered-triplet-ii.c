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
#define stack_bottom(S) (S.arr[0])
#define stack_nums(S) (S.ctr)
#define MAX(a, b) (a > b ? a : b)

long long maximumTripletValue(int* nums, int numsSize) {
    stack_t s = stack_init(numsSize);
    long long ret = -1;
    int max_diff = 0;
    for (int i = 0; i < numsSize; i++) {
        if (max_diff > 0) {
            // - Use current max_diff to calculate the result in this round.
            // - To avoid overflow, casting `(long long)max_diff` is required.
            long long tmp = (long long)max_diff * nums[i];
            ret = MAX(ret, tmp);
        }
        // Maintain monotonic stack
        while (stack_nums(s) > 0 && stack_top(s) < nums[i]) {
            stack_pop(s);
        }
        stack_push(s, nums[i]);
        // Calcualte current max diff from the monotonic stack
        if (stack_nums(s) >= 2) {
            int stack_max = stack_bottom(s) - stack_top(s);
            max_diff = MAX(max_diff, stack_max);
        }
    }
    stack_dinit(s);
    return (ret < 0 ? 0 : ret);
}
