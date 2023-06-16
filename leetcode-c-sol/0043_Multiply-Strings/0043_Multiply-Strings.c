
char * multiply(char * num1, char * num2)
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    char *ret = calloc(len1+len2+1, sizeof(char));
    for (int i = len1 - 1; i >= 0; i--) 
    {
        for (int j = len2 - 1; j >= 0; j--) 
        {            
            int mul = (num1[i] - '0')*(num2[j] - '0');
            int base1 = i + j;
            int base2 = i + j + 1;
            int sum = mul + ret[base2];
            ret[base1] += sum / 10;
            ret[base2] = sum % 10;
        }
    }
    
    int retIdx = 0;
    for (int x = 0; x < len1+len2; x++)
    {
        ret[x] += '0';
        if (ret[retIdx] == '0' && retIdx < (len1+len2-1))
        {
            retIdx++;
        }
    }
    
    return &(ret[retIdx]);
}

