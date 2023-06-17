char * replaceDigits(char * s)
{
    // notice that 1 <= leng <= 100
    int len = strlen(s);
    for (int i = 1; i < len; i += 2)
        s[i] = s[i-1] + (s[i] - '0');

    return s;
}
