bool validHexChar(char c)
{
	if (('0' <= c & c <= '9') ||
			('a' <= c & c <= 'f') ||
			('A' <= c & c <= 'F'))
	{
		return true;
	}
	return false;
}

bool validIPv6(char *s)
{
	int len = strlen(s);
	int strCtr = 0;
	int groupCtr = 0;
	char *delim = ":";
	char *pch;
	pch = strtok(s, delim);
	while (pch != NULL)
	{
		int hexCtr = 0;        
		char *tmp = pch;
		while (*tmp)
		{
			if (!validHexChar(*tmp))
			{
				return false;
			}
			hexCtr++;
			strCtr++;
			tmp++;            
		}

		if (hexCtr > 4)
		{
			return false;
		}
		pch = strtok(NULL, delim);
		groupCtr++;
	} 

	return (groupCtr != 8 || len - strCtr != 7) ? false : true;
}

bool validIPv4(char *s)
{
	int len = strlen(s);
	int strCtr = 0;
	int groupCtr = 0;
	char *delim = ".";
	char *pch;
	pch = strtok(s, delim);
	while (pch != NULL)
	{
		int num = 0, gotZero = 0;
		char *tmp = pch;
		while (*tmp)
		{
			if (*tmp < '0' || *tmp > '9' || gotZero)
			{
				return false;
			}
			if (*tmp == '0')
			{                
				gotZero = 1;
			}
			strCtr++;
			num *= 10;
			num += *tmp - '0';
			tmp++;
			if (num < 0 || num > 255)
			{
				return false;
			}
		}
		pch = strtok(NULL, delim);
		groupCtr++;
	}      

	return (groupCtr != 4 || len - strCtr != 3) ? false : true;
}

char * validIPAddress(char * IP)
{
	// IPv4: 
	if (NULL != strchr(IP, '.'))
	{
		return (validIPv4(IP) ? "IPv4" : "Neither");
	} else
	{
		return (validIPv6(IP) ? "IPv6" : "Neither");
	}
}

