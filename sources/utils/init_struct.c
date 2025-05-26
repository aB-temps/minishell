#include "input.h"

void	init_input(t_input *input)
{
	input->token = (void *)0;
	input->prev = (void *)0;
	input->next = (void *)0;
}
void	init_token(t_token *token)
{
	token->type = -1;
	token->content = (void *)0;
}