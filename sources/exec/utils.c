#include "input.h"
#include "builtins.h"

char	*get_type(ssize_t type)
{
	const char *types[11] = {
		"COMMAND",
		"ARG",
		"PIPE",
		"REDIR_IN",
		"REDIR_OUT",
		"APPEND",
		"HEREDOC",
		"ASSIGN",
		"S_QUOTES",
		"D_QUOTES",
		"ENV_VAR",
	};
	return ((char *)types[type]);
}

int	is_builtin(t_token current_token)
{
	char	**cmd;

	cmd = ((char **)current_token.formatted_content);
	ft_printf("%s\n", cmd[0]);
	if (!ft_strncmp(cmd[0],"echo", ft_strlen(cmd[0])))
	{
		printf("Je lance echo du pauvre\n");
		ft_echo(cmd);
		return (1);
	}
	return (0);
}

char	*get_cmd_by_index(t_input *input, t_token *tokens_array, int index)
{
	int	i;
	int	cmd_count;

	i = 0;
	cmd_count = 0;
	while (i < input->token_qty)
	{
		if (tokens_array[i].type == COMMAND)
			cmd_count++;
		if (cmd_count - 1 == index)
			return (((char **)tokens_array[i].formatted_content)[0]);
		i++;
	}
	return (NULL);
}

int	count_cmd(t_input *input)
{
	int		i;
	int		cmd_count;
	t_token	*tokens_array;

	i = 0;
	cmd_count = 0;
	tokens_array = (t_token *)input->v_tokens->array;
	while (i < input->token_qty)
	{
		if (tokens_array[i].type == COMMAND)
			cmd_count++;
		i++;
	}
	return (cmd_count);
}
