static inline char* reverse(char *str)
{
    int tail = strlen(str) - 1, head = 0;
    while (head < tail) {
        char t = str[head];
        str[head] = str[tail];
        str[tail] = t;
        head++;
        tail--;
    }
    return str;
}

int monotoneIncreasingDigits(int n)
{
    char *str = calloc(11, sizeof(char));
    int cur_digit = 0, all9_digit = 0;
    int pre = n % 10, cur = n / 10;
    while (cur) {
        int tmp = cur % 10;
        if (tmp <= pre) {
            str[cur_digit] = pre + '0';
            pre = tmp;
        } else {
            for (int i = cur_digit; i >= all9_digit; i--)
                str[i] = '9';
            // Avoid duplicate assignment
            all9_digit = cur_digit;   
            pre = tmp - 1;
        }
        cur_digit++;
        cur /= 10;
    }

    if (pre)
        str[cur_digit] = pre + '0';

    return atoi(reverse(str));
}
