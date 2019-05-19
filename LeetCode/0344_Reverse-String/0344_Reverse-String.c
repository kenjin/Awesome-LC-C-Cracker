
void reverseString(char* s, int sSize)
{
    int head = 0;
    int tail = sSize-1;
    while (head < tail)
    {
        char tmp = s[head];
        s[head] = s[tail];
        s[tail] = tmp;
        head++;
        tail--;
    }
}

