#include "exec.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*preprocess_command(char *cmd_str);

/**
 * @brief Initialize the s_input structure
 * @param input Pointer to the structure to initialize
 */
void	init_input(t_input *input)
{
	if (!input)
		return ;
	input->token_qty = 0;
	input->token = NULL;
}

/**
 * @brief Initialize a token structure
 * @param token Pointer to the token to initialize
 */
void	init_token(t_token *token)
{
	if (!token)
		return ;
	token->type = -1;
	token->raw_content = NULL;
	token->formatted_content = NULL;
}

/**
 * @brief Sets up an input structure with a specified number of tokens
 * @param input Pointer to the input structure to initialize
 * @param token_count Number of tokens to allocate
 * @return 0 on success, -1 on failure
 */
int	setup_input_structure(t_input *input, size_t token_count)
{
	size_t	i;

	if (!input)
		return (-1);
	init_input(input);
	if (token_count > 0)
	{
		input->token = malloc(sizeof(t_token) * token_count);
		if (!input->token)
			return (-1);
		for (i = 0; i < token_count; i++)
		{
			init_token(&input->token[i]);
		}
		input->token_qty = token_count;
	}
	return (0);
}

/**
 * @brief Processes a command string and fills the input structure for execution
 * @param input Pointer to the input structure to fill
 * @param cmd_str Command string to process (e.g. "ls -la | grep a")
 * @return 0 on success, -1 on failure
 */
int	process_command_string(t_input *input, char *cmd_str)
{
	char	**tokens;
	size_t	token_count;
	size_t	i;
	char	*processed_str;

	tokens = NULL;
	token_count = 0;
	i = 0;
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
	int command_mode = 1;
	for (i = 0; i < token_count; i++)
	{
		if (strcmp(tokens[i], "|") == 0)
		{
			input->token[i].type = PIPE;
			command_mode = 1;
		}
		else if (strcmp(tokens[i], "<") == 0)
			input->token[i].type = REDIR_IN;
		else if (strcmp(tokens[i], ">") == 0)
			input->token[i].type = REDIR_OUT;
		else if (strcmp(tokens[i], "<<") == 0)
			input->token[i].type = HEREDOC;
		else if (strcmp(tokens[i], ">>") == 0)
			input->token[i].type = REDIR_OUT;
		else if (command_mode)
		{
			input->token[i].type = COMMAND;
			command_mode = 0;
		}
		else
			input->token[i].type = ARG;
		input->token[i].raw_content = ft_strdup(tokens[i]);
		if (!input->token[i].raw_content)
		{
			free_input_content(input);
			free_tab_return_null(tokens);
			return (-1);
		}
		input->token[i].formatted_content = input->token[i].raw_content;
	}
	free_tab_return_null(tokens);
	return (0);
}

/**
 * @brief Preprocesses a command string to separate operators
 * @param cmd_str Original command string

	* @return Newly allocated preprocessed string with operators separated by spaces
 */
char	*preprocess_command(char *cmd_str)
{
	size_t	max_len;
	char	*result;
	size_t	i;
	size_t	j;

	if (!cmd_str)
		return (NULL);
	max_len = strlen(cmd_str) * 3 + 1;
	result = malloc(max_len);
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

/**
 * @brief Frees all allocated memory in an input structure
 * @param input Pointer to the input structure to clean
 */
void	free_input_content(t_input *input)
{
	size_t	i;

	if (!input)
		return ;
	if (input->token)
	{
		for (i = 0; i < input->token_qty; i++)
		{
			if (input->token[i].raw_content)
				free(input->token[i].raw_content);
			if (input->token[i].formatted_content
				&& input->token[i].formatted_content != input->token[i].raw_content)
				free(input->token[i].formatted_content);
		}
		free(input->token);
	}
	init_input(input);
}

/**
 * @brief Frees an array of strings
 * @param arr Array of strings to free
 */
void	free_str_array(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	for (i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

/**
 * @brief Simple readline implementation if not using GNU readline
 * @return Newly allocated string containing the line read
 */
char	*readline(void)
{
	char	*line;
	size_t	len;
	ssize_t	read;

	line = NULL;
	len = 0;
	read = getline(&line, &len, stdin);
	if (read == -1)
	{
		free(line);
		return (NULL);
	}
	if (read > 0 && line[read - 1] == '\n')
		line[read - 1] = '\0';
	return (line);
}

int	print_cmd(t_input *input, char **env)
{
	for (size_t i = 0; i < input->token_qty; i++)
	{
		printf("'%s' : ", input->token[i].raw_content);
		switch (input->token[i].type)
		{
		case COMMAND:
			printf("COMMAND\n");
			break ;
		case ARG:
			printf("ARGUMENT\n");
			break ;
		case PIPE:
			printf("PIPE\n");
			break ;
		case REDIR_IN:
			printf("REDIRECTION IN\n");
			break ;
		case REDIR_OUT:
			printf("REDIRECTION OUT\n");
			break ;
		case HEREDOC:
			printf("HEREDOC\n");
			break ;
		default:
			printf("type=%zd\n", input->token[i].type);
		}
	}
	printf("\n");
	(void)env;
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_input	input;
	char	*line;

	(void)argv;
	(void)argc;
	while (1)
	{
		printf("minishell> ");
		line = readline();
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
		if (process_command_string(&input, line) == 0)
		{
			print_cmd(&input, env);
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
