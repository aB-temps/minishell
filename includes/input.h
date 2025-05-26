#ifndef INPUT_H
# define INPUT_H

# include <sys/types.h>

enum					token_type
{
	CACA,
};

typedef struct s_input	t_input;
typedef struct s_token	t_token;

struct					s_token
{
	ssize_t				type;
	void				*content;
};

struct					s_input
{
	t_token				*token;
	t_input				*prev;
	t_input				*next;
};

void					init_input(t_input *input);
void					init_token(t_token *token);

#endif
