#include "input.h"

void	init_input(t_input *input, char *line)
{
	input->token_qty = 0;
	input->v_tokens = (void *)0;
	input->line = line;
}
void	init_token(t_token *token)
{
	token->type = -1;
	token->raw_content = (void *)0;
	token->formatted_content = (void *)0;
}