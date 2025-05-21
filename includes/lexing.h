#ifndef LEXING_H
# define LEXING_H

# include "libft.h"
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_PIPE,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_IN,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_WHITESPACE,
	TOKEN_UNKNOWN,
	TOKEN_ERROR
}			t_token_type;

// typedef struct s_lexing
// {
// 	char	**tab_lexing;
// }			t_lexing;

typedef struct s_token
{
	int		type;
	char	*content;
}			t_token;

int			lexing(char *line);

#endif