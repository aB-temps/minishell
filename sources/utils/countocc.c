#include "token_formatting.h"

// size_t	countocc(char *s, char *to_find)
// {
// 	size_t count;
// 	char *cursor;

// 	count = 0;
// 	cursor = s;
// 	while (to_find && cursor)
// 	{
// 		cursor = ft_strnstr(s, to_find, ft_strlen(s));
// 		if (cursor)
// 			count++;
// 		s = cursor + ft_strlen(to_find);
// 	}
// 	printf("%s => count = %zu\n", to_find, count);
// 	return (count);
// }

char	*wordnword(const char *big, const char *little, size_t len)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while ((i + j) < len && big[j])
	{
		i = 0;
		while (little[i] == big[j + i] && i + j < len&& big[j] != '$' && !is_whitespace(big[j]))
		{
			i++;
			if (little[i] == '\0')
				return (&((char *)big)[j]);
		}
		j++;
	}
	return (NULL);
}

size_t	countocc(char *s, char *to_find)
{
	size_t	count;
	char	*cursor;

	count = 0;
	cursor = s;
	while (to_find && cursor)
	{
		cursor = wordnword(s, to_find, ft_strlen(s));
		printf("cursor : '%s'\n", cursor);
		if (cursor)
			count++;
		s = cursor + ft_strlen(to_find);
	}
	printf("'%s' => count = %zu\n", to_find, count);
	return (count);
}
