typedef struct _stack {
    char* arr;
    int ctr;
    int size;
} STACK;

#define stack_init(SZ) {.arr = calloc(SZ, sizeof(char)), .ctr = 0, .size = SZ}
#define stack_dinit(S)      do {free(S.arr);} while(0)
#define stack_push(S, IDX) do {S.arr[S.ctr++] = IDX;} while (0)
#define stack_pop(S)       (S.arr[--S.ctr])
#define stack_cur_size(S)  (s.ctr)
#define stack_top(S)       (S.arr[S.ctr - 1])
#define stack_is_empty(S)  (S.ctr == 0 ? true : false)

char* removeKdigits(char* num, int k) {
    int len = strlen(num), idx = 0;
    STACK s = stack_init(len);
    // Monotonic stack with ascending elements
    while (idx < len && k > 0) {
        if (!stack_is_empty(s) && stack_top(s) > num[idx]) {
            stack_pop(s);
            k--;
        } else {
            stack_push(s, num[idx++]);
        }
    }
    // Push the rest of digit
    while (idx < len)
        stack_push(s, num[idx++]);
    // Pop the rest of k digit from monotonic stack
    while (k > 0) {
        stack_pop(s);
        k--;
    }

    /* remove leading zero */
    bool lead_zero = true;
    int ret_ctr = 0;
    for (int x = 0; x < stack_cur_size(s); x++) {
        if (s.arr[x] != '0' || (!lead_zero && s.arr[x] == '0')) {
            lead_zero = false;
            num[ret_ctr++] = s.arr[x];
        }
    }
    num[ret_ctr] = 0;

    stack_dinit(s);
    return (lead_zero ? "0" : num);
}
