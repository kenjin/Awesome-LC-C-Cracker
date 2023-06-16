
bool isAnagram(char * s, char * t)
{
	int s_set[26] = {0}, t_set[26] = {0};
	while (*s) {
		s_set[*s - 'a'] += 1;
		s++;
	}

	while (*t) {
		t_set[*t - 'a'] += 1;
		t++;
	}

	for (int i = 0; i < 26; i++) {
		if (s_set[i] != t_set[i])
			return false;
	}
	return true;
}
