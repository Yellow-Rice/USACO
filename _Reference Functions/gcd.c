int gcd(int i, int j)
{
	if (i < 0 || j < 0) {
		return -1;
	}

	int r = 1;
	while (r) {
		r = i % j;
		i = j;
		j = r;
	}
	return i;
}
