/*
 *retval < 0, a/b < c/d
 *retval = 0, a/b = c/d
 *retval > 0, a/b > c/d
 */

int fraction_compare(int a, int b, int c, int d)
{
	return a * d - b * c;
}
