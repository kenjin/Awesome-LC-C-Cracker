
bool isVowel(char c)
{
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

char * reverseVowels(char * s)
{
    int len = strlen(s);
    int head = 0;
    int tail = len-1;
    
    while (head < tail)
    {
        while (head < len && !isVowel(s[head]))
        {
            head++;
        }
        
        while (tail >= 0 && !isVowel(s[tail]))
        {
            tail--;
        }
        
        
        if (head < tail)
        {
            char tmp = s[head];
            s[head] = s[tail];
            s[tail] = tmp;
        }
        head++;        
        tail--;
    }

    return s;
}

