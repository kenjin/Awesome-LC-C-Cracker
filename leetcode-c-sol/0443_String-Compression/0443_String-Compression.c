
void reverse(char *s, int head, int tail)
{
	while (head < tail)
	{
		char tmp = s[head];
		s[head] = s[tail];
		s[tail] = tmp;
		head++;
		tail--;
	}
}

int repeatHandler(char *chars, int repeat, int baseIdx)
{
	int base = baseIdx;
	if (repeat > 1)
	{
		while (repeat/10)
		{
			chars[baseIdx] = (repeat%10) + '0';
			baseIdx++;
			repeat /= 10;
		}        
		chars[baseIdx] = (repeat%10) + '0';
		reverse(chars, base, baseIdx);
		baseIdx++;
	}

	return baseIdx;
}

int compress(char* chars, int charsSize)
{
	char prev = chars[0];
	int repeat = 1;
	int baseIdx = 0;
	for (int i = 1; i < charsSize; i++)
	{
		if (prev == chars[i])
		{
			repeat++;
		} else
		{
			// Update char
			chars[baseIdx] = prev;
			baseIdx++;
			// Repeat Handler
			baseIdx = repeatHandler(chars, repeat, baseIdx);
			// Assign new prev
			prev = chars[i];
			repeat = 1;
		}
	}
	// Update char
	chars[baseIdx] = prev;
	baseIdx++;
	// Repeat Handler
	baseIdx = repeatHandler(chars, repeat, baseIdx);

	return baseIdx;
}


