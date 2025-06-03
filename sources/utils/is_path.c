#include <stdbool.h>

bool	is_path(char c)
{
	return (c == '.' || c == '/' || c == '~');
}