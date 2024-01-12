bool halvesAreAlike(char* s)
{
    int len = strlen(s);
    int a_ctr = 0, b_ctr = 0;
    for (int i = 0; i < (len >> 1); i++){
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'||
            s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U')
            a_ctr++;
    }
    for (int i = (len >> 1); i < len; i++){
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'||
            s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U')
            b_ctr++;
    }
    return (a_ctr == b_ctr);
}
