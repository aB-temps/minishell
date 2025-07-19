#include "token_formatting.h"

size_t	countocc(char *s, char *to_find)
{
	size_t	count;
	char	*cursor;

	count = 0;
	cursor = s;
	while (to_find && cursor)
	{
		cursor = ft_strnstr(s, to_find, ft_strlen(s));
		if (cursor/*  && !ft_strncmp(to_find, cursor, ft_strlen(s)) */)
			count++;
		s = cursor + ft_strlen(to_find);
	}
	return (count);
}