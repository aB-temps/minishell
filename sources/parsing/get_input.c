#include "debug.h"
#include "exec.h"
#include "libft.h"
#include "parsing.h"
#include "style.h"
#include <linux/limits.h>
#include <unistd.h>

char	*get_line(char **prompt)
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
		if (!build_prompt(&input->prompt))
			input->prompt = ft_strdup("$ ");
		if (!input->prompt)
			exit_minishell(input, input->last_exit_status);
		input->line = readline(input->prompt);
		if (!input->line)
			exit_minishell(input, input->last_exit_status);
		if (is_valid_input(input->line))
		{
			if (parse_input(input))
				input->last_exit_status = exec_cmd(input,
													/* env_list_to_array(input->env) */ env,
													&input->last_exit_status);
			clear_vector(input->v_tokens);
			input->token_qty = 0;
		}
		free(input->line);
		input->line = (void *)0;
		free(input->prompt);
		input->prompt = (void *)0;
	}
}
// void	get_input(char **env)
// {
// 	int		exit_status;
// 	t_list	*l_env;
// 	t_input	*input;
// 	char	*line;
// 	char	*prompt;

// 	exit_status = 0;
// 	l_env = env_to_list(env);
// 	if (!l_env)
// 		return ;
// 	line = (void *)0;
// 	while (1)
// 	{
// 		input = (void *)0;
// 		if (!build_prompt(&prompt))
// 			prompt = ft_strdup("minishell $ ");
// 		if (!prompt)
// 			break ;
// 		line = readline(prompt);
// 		free(prompt);
// 		if (!line)
// 			break ;
// 		add_history(line);
// 		if (is_valid_input(line))
// 		{
// 			input = parse_input(line, prompt, exit_status, l_env);
// 		}
// 		if (input)
// 		{
// 			exit_status = exec_cmd(input, env, &input->last_exit_status);
// 			clear_vector(input->v_tokens);
// 			free(input);
// 		}
// 		free(line);
// 	}
// }
