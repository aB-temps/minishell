#ifndef INPUT_H
# define INPUT_H

# include <sys/types.h>

enum					token_type
{
	COMMAND,
	ARG,
	PIPE,
	REDIR_OUT,
	REDIR_IN,
	HEREDOC,
	APPEND,
	ASSIGN,
	S_QUOTES,
	D_QUOTES,
	ENV_VAR,
};

typedef struct s_input	t_input;
typedef struct s_token	t_token;

struct					s_input
{
	ssize_t				token_qty;
	t_token				*token;
};

struct					s_token
{
	ssize_t				type;
	char				*raw_content;
	void				*formatted_content;
};


void					init_input(t_input *input);
void					init_token(t_token *token);

#endif
