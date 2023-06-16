
int rotatedDigits(int N)
{
    int ret = 0;
    for (int i = 0; i <= N; i++)
    {
        int cur = i;
        char fail = 0, rotate = 0;
        while (cur > 0)
        {
            int tmp = cur % 10;                            
            if (tmp == 2 || tmp == 5 || tmp == 6 || tmp == 9)
            {
                rotate = 1;                
            } else if (tmp == 3 || tmp == 4 || tmp == 7)
            {
                fail = 1;
                break;
            }
            cur /= 10;
        }
        
        if (!fail && rotate)
        {
            ret++;
        } 
                
    }
    return ret;
}
