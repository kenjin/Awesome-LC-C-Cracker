static inline void reverse_str(char *word, int head, int tail)
{
    while (head < tail) {
        char tmp = word[tail];
        word[tail] = word[head];
        word[head] = tmp;
        head++;
        tail--; 
    }
}

char* reversePrefix(char* word, char ch)
{
    int tail = 0;
    while (word[tail] && word[tail] != ch)
        tail++;

    if (word[tail])
        reverse_str(word, 0, tail);

    return word;
}
