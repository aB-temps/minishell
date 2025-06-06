#ifndef INPUT_H
# define INPUT_H

# include "libft.h"
# include <sys/types.h>

enum					token_type
{
	COMMAND,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	ASSIGN,
	S_QUOTES,
	D_QUOTES,
	ENV_VAR,
};

typedef struct s_input	t_input;
typedef struct s_token	t_token;

struct					s_token
{
	ssize_t				type;
	char				*raw_content;
	void				*formatted_content;
};

struct					s_input
{
	ssize_t				token_qty;
	t_vector			*v_tokens;
	char				*line;
};

void					init_input(t_input *input, char *line);
void					init_token(t_token *token);
void					create_token(t_input *input, int type,
							char *raw_content);
void					clear_token(t_vector *tokens);
void					exit_minishell(t_input *input, int exit_code);

#endif
