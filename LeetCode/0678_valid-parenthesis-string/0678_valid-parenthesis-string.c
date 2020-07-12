
bool checkValidString(char *s)
{
    int stack = 0, len = 0;
    char *tmp = s;
    while (*tmp) {
        stack += (*tmp != ')' ? 1 : -1); /* '(' or '*' */
        if (stack < 0)
            return false;
        tmp++;
        len++;
    }
    stack = 0;
    for (int i = len - 1; i >= 0; i--) {
        stack += (s[i] != '(' ? 1 : -1); /* ')' or '*' */
        if (stack < 0)
            return false;
    }

    return true;
}
