#include "exec.h"
#include "input.h"

void	exit_minishell(t_input *input, int exit_code)
{
	if (input)
	{
		if (input->v_tokens)
			clear_vector(&input->v_tokens);
		if (input->env)
		{
			free_tab_return_null(input->env->array);
			ft_lstclear(&input->env->list, &clear_env_list);
			free(input->env);
		}
		if (input->line)
			free(input->line);
		if (input->prompt)
			free(input->prompt);
		free(input);
	}
	exit(exit_code);
}
