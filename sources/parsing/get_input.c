#include "debug.h"
#include "exec.h"
#include "libft.h"
#include "parsing.h"
#include "style.h"
#include <linux/limits.h>
#include <unistd.h>

void	reset_input(t_input *input)
{
	free(input->prompt);
	free(input->line);
	input->prompt = (void *)0;
	input->line = (void *)0;
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
	t_input	*input;

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
				input->last_exit_status = exec_cmd(input, input->env->array,
						&input->last_exit_status);
			clear_vector(input->v_tokens);
		}
		reset_input(input);
	}
}
