
bool judgeCircle(char * moves)
{
    int vertical = 0;
    int horizon = 0;
    int i = 0;
    while (moves[i] != '\0')
    {
        switch (moves[i])
        {
            case 'U':
                vertical++;
                break;
            case 'D':
                vertical--;
                break;
            case 'R':
                horizon++;
                break;
            case 'L':
                horizon--;
                break;
            default:
                break;
        }
        i++;
    }
    return ((vertical == 0) && (horizon == 0)) ? true : false;
}

