int minimumLength(char* s)
{
   int head = 0, tail = strlen(s) - 1;
   while (head < tail && s[head] == s[tail]) {
        // Move the head pointer for continuous prefix.
        while (head + 1 < tail && s[head] == s[head + 1])
            head++;
        // Move the tail pointer for continuous suffix.
        while (tail - 1 > head && s[tail] == s[tail - 1])
            tail--;

        head++;
        tail--;
   }
   return (head <= tail ? (tail - head + 1) : 0);
}
