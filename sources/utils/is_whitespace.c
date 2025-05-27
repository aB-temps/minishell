# include <stdbool.h>

bool	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}