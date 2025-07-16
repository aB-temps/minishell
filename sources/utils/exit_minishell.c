#include "exec.h"
#include "input.h"

void	clear_env_list(void *var)
{
	free(((t_env_var *)var)->key);
	free(((t_env_var *)var)->value);
	free(var);
}

void	exit_minishell(t_input *input, int exit_code)
{
	if (input)
	{
		if (input->v_tokens)
			clear_vector(input->v_tokens);
		if (input->env)
			ft_lstclear(&input->env, &clear_env_list);
		if (input->line)
			free(input->line);
		if (input->prompt)
			free(input->prompt);
		free(input);
	}
	exit(exit_code);
}
