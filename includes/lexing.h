#ifndef LEXING_H
# define LEXING_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_WORD,			//0
	TOKEN_SINGLE_QUOTE,	//1
	TOKEN_DOUBLE_QUOTE,	//2
	TOKEN_PIPE,			//3
	TOKEN_VARIABLE,		//4
	TOKEN_REDIRECT_OUT,	//5
	TOKEN_REDIRECT_IN,	//6
	TOKEN_APPEND,		//7
	TOKEN_HEREDOC,		//8
	TOKEN_WHITESPACE,	//9
	TOKEN_UNKNOWN,		//11
	TOKEN_ERROR = 404	//12
}			t_token_type;

typedef struct s_token
{
	int		type;
	char	*content;
}			t_token;

int			lexing(char *line, t_list **token_lst);

#endif