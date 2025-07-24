#include "style.h"
#include "token_formatting.h"
#include <linux/limits.h>
#include <unistd.h>

char	*build_ps1(t_input *input)
{
	char	*ps1;
	char	*username;

	ps1 = (void *)0;
	username = get_env_value("USER", input);
	if (!ft_strlen(username))
		return (username);
	ps1 = ft_strjoin(FG_GREEN, username);
	free(username);
	if (!ps1)
		exit_minishell(input, EXIT_FAILURE);
	ps1 = str_free_to_join(ps1, " ");
	if (!ps1)
		exit_minishell(input, EXIT_FAILURE);
	return (ps1);
}

char	*build_ps2(t_input *input)
{
	char	*ps2;
	char	*pwd;

	ps2 = (void *)0;
	pwd = get_env_value("PWD", input);
	ps2 = ft_strjoin(FG_WHITE "[" FG_BLUE, pwd);
	free(pwd);
	if (!ps2)
		exit_minishell(input, EXIT_FAILURE);
	ps2 = str_free_to_join(ps2, FG_WHITE "]\n⚡ " R_ALL);
	if (!ps2)
		exit_minishell(input, EXIT_FAILURE);
	return (ps2);
}

void	build_prompt(t_input *input)
{
	char	*ps1;
	char	*ps2;

	ps1 = build_ps1(input);
	ps2 = build_ps2(input);
	input->prompt = ft_strjoin(ps1, ps2);
	free(ps1);
	free(ps2);
	if (!input->prompt)
		exit_minishell(input, EXIT_FAILURE);
}
