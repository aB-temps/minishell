#include "debug.h"
#include "exec.h"
#include "parsing.h"
#include <linux/limits.h>

void	reset_input(t_input *input)
{
	if (input->prompt)
	{
		free(input->prompt);
		input->prompt = (void *)0;
	}
	if (input->line)
	{
		free(input->line);
		input->line = (void *)0;
	}
	input->token_qty = 0;
}

char	*prompt_user(char **prompt)
{
	char	*line;

	if (!build_prompt(prompt))
		*prompt = ft_strdup("minishell $ ");
	if (!*prompt)
		return ((void *)0);
	line = readline(*prompt);
	return (line);
}

void	get_input(char **env)
{
	t_input *input;

	input = ft_calloc(1, sizeof(t_input));
	if (!input)
		exit(EXIT_FAILURE);
	input->env = init_env(env);
	if (!input->env)
		exit_minishell(input, EXIT_FAILURE);
	while (1)
	{
		input->line = prompt_user(&input->prompt);
		if (!input->line)
			exit_minishell(input, input->last_exit_status);
		if (is_valid_input(input->line))
		{
			if (parse_input(input))
				start_exec(input);
			clear_vector(&input->v_tokens);
		}
		add_history(input->line);
		reset_input(input);
	}
}