#include "exec.h"
#include "input.h"
#include "libft.h"
#include "parsing.h"
#include "style.h"
#include <linux/limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*preprocess_command(char *cmd_str);
void	clear_token_content(t_vector *vec);

void	clear_token_content(t_vector *vec)
{
	size_t	i;
	t_token	*token;

	if (!vec || !vec->array)
		return ;
	for (i = 0; i < vec->nb_elements; i++)
	{
		token = get_token_at_index(vec, i);
		if (token->raw_content)
			free(token->raw_content);
		if (token->formatted_content
			&& token->formatted_content != token->raw_content)
			free(token->formatted_content);
	}
}

void	init_input(t_input *input)
{
	if (!input)
		return ;
	input->token_qty = 0;
	input->v_tokens = create_vector(5, sizeof(t_token), clear_token_content);
}

void	init_token(t_token *token)
{
	if (!token)
		return ;
	token->type = -1;
	token->raw_content = NULL;
	token->formatted_content = NULL;
}

int	setup_input_structure(t_input *input, size_t token_count)
{
	if (!input)
		return (-1);
	init_input(input);
	if (!input->v_tokens)
		return (-1);
	if (token_count > 0 && !grow_vector(input->v_tokens, token_count))
		return (-1);
	return (0);
}

int	process_command_string(t_input *input, char *cmd_str)
{
	char	**tokens;
	size_t	token_count;
	size_t	i;
	char	*processed_str;
	int		command_mode;
	t_token	token;

	tokens = NULL;
	token_count = 0;
	command_mode = 1;
	if (!input || !cmd_str)
		return (-1);
	processed_str = preprocess_command(cmd_str);
	if (!processed_str)
		return (-1);
	tokens = ft_split(processed_str, ' ');
	free(processed_str);
	if (!tokens)
		return (-1);
	while (tokens[token_count])
		token_count++;
	if (setup_input_structure(input, token_count) == -1)
	{
		free_tab_return_null(tokens);
		return (-1);
	}
	for (i = 0; i < token_count; i++)
	{
		init_token(&token);
		if (strcmp(tokens[i], "|") == 0)
		{
			token.type = PIPE;
			command_mode = 1;
		}
		else if (strcmp(tokens[i], "<") == 0)
			token.type = REDIR_IN;
		else if (strcmp(tokens[i], ">") == 0)
			token.type = REDIR_OUT;
		else if (strcmp(tokens[i], "<<") == 0)
			token.type = HEREDOC;
		else if (strcmp(tokens[i], ">>") == 0)
			token.type = APPEND;
		else if (command_mode)
		{
			token.type = COMMAND;
			command_mode = 0;
		}
		else
			token.type = ARG;
		token.raw_content = ft_strdup(tokens[i]);
		if (!token.raw_content)
		{
			free_input_content(input);
			free_tab_return_null(tokens);
			return (-1);
		}
		token.formatted_content = token.raw_content;
		if (!add_element(input->v_tokens, &token))
		{
			free(token.raw_content);
			free_input_content(input);
			free_tab_return_null(tokens);
			return (-1);
		}
		input->token_qty++;
	}
	free_tab_return_null(tokens);
	return (0);
}

char	*preprocess_command(char *cmd_str)
{
	size_t	max_len;
	char	*result;
	size_t	i;
	size_t	j;

	if (!cmd_str)
		return (NULL);
	max_len = strlen(cmd_str) * 3 + 1;
	result = ft_calloc(max_len, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd_str[i])
	{
		if (cmd_str[i] == '|' || cmd_str[i] == '<' || cmd_str[i] == '>')
		{
			if (j > 0 && result[j - 1] != ' ')
				result[j++] = ' ';
			if ((cmd_str[i] == '>' || cmd_str[i] == '<') && cmd_str[i
				+ 1] == cmd_str[i])
			{
				result[j++] = cmd_str[i++];
				result[j++] = cmd_str[i];
			}
			else
			{
				result[j++] = cmd_str[i];
			}
			if (cmd_str[i + 1] && cmd_str[i + 1] != ' ')
				result[j++] = ' ';
		}
		else
		{
			result[j++] = cmd_str[i];
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	free_input_content(t_input *input)
{
	if (!input || !input->v_tokens)
		return ;
	clear_vector(input->v_tokens);
	input->v_tokens = NULL;
	input->token_qty = 0;
}

void	free_str_array(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	for (i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

// int	print_cmd(t_input *input, char **env)
// {
// 	t_token	*token;

// 	for (size_t i = 0; i < input->token_qty; i++)
// 	{
// 		token = get_token_at_index(input->v_tokens, i);
// 		if (!token)
// 			continue ;
// 		printf("'%s' : ", token->raw_content);
// 		switch (token->type)
// 		{
// 		case COMMAND:
// 			printf("COMMAND\n");
// 			break ;
// 		case ARG:
// 			printf("ARGUMENT\n");
// 			break ;
// 		case PIPE:
// 			printf("PIPE\n");
// 			break ;
// 		case REDIR_IN:
// 			printf("REDIRECTION IN\n");
// 			break ;
// 		case REDIR_OUT:
// 			printf("REDIRECTION OUT\n");
// 			break ;
// 		case APPEND:
// 			printf("APPEND\n");
// 			break ;
// 		case HEREDOC:
// 			printf("HEREDOC\n");
// 			break ;
// 		default:
// 			printf("type=%zd\n", token->type);
// 		}
// 	}
// 	printf("\n");
// 	(void)env;
// 	return (0);
// }

int	main(int argc, char **argv, char **env)
{
	t_input input;
	char *line;

	(void)argv;
	(void)argc;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("\nExiting shell...\n");
			break ;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		else
			add_history(line);
		if (process_command_string(&input, line) == 0)
		{
			exec_cmd(&input, env);
			free_input_content(&input);
		}
		else
		{
			printf("Failed to process command\n");
		}
		free(line);
	}
	return (0);
}