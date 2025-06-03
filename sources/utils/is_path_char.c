#include <stdbool.h>

bool	is_path_char(char c)
{
	return (c == '.' || c == '/' || c == '~');
}