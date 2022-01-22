
bool isValid(char * s)
{
	int len = strlen(s), stack_ctr = -1;
	char stack[len+1];

	while (*s) {
		if (*s == '(' || *s == '{' || *s == '[') {
			stack[++stack_ctr] = *s;
		} else {
			if (stack_ctr < 0 || *s < stack[stack_ctr] || *s - stack[stack_ctr] > 2)
				return false; 
			stack_ctr--;
		}
		s++;
	}
	return (stack_ctr < 0 ? true : false);
}
