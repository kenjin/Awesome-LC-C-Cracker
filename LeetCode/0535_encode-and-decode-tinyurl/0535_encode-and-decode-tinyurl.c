char map[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // 62 chars
char *database[5000];
long id = 1;

/** Encodes a URL to a shortened URL. */
char* encode(char* longUrl) 
{    
	int len = strlen(longUrl);
	database[id] = calloc(len+1, sizeof(char));
	strcpy(database[id], longUrl);        

	// Example: http://tinyurl.com/ABCDEF
	char *ret = calloc(27, sizeof(char));
	char buf[7] = {0};
	strcpy(buf, "aaaaaa");
	int idx = 5;
	int tmp = id;
	while (tmp > 0)
	{
		buf[idx] = map[tmp % 62];
		idx--;
		tmp = tmp / 62;
	}
	id++;
	sprintf(ret, "http://tinyurl.com/%s", buf);
	return ret;
}

/** Decodes a shortened URL to its original URL. */
char* decode(char* shortUrl) 
{
	char *ptr = shortUrl + 19;  // "http://tinyurl.com"
	int id = 0;
	for (int i = 0; i < 6; i++)
	{
		id *= 62;
		int tmp;
		if (ptr[i] >= 'A' && ptr[i] <= 'Z')
		{
			tmp = ptr[i] - 'A' + 26;
		} else if (ptr[i] >= 'a' && ptr[i] <= 'z')
		{
			tmp = ptr[i] - 'a';
		} else
		{
			tmp = ptr[i] - '0' + 52;
		}
		id += tmp;
	}

	return database[id];
}

// Your functions will be called as such:
// char* s = encode(s);
// decode(s);
