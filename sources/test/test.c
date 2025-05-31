#include "exec.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*preprocess_command(char *cmd_str);
void	clear_token_content(t_vector *vec);
t_token	*get_token_at_index(t_vector *vec, size_t index);

/**
 * @brief Cleanup function for tokens in vector
 */
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
        if (token->formatted_content && 
            token->formatted_content != token->raw_content)
            free(token->formatted_content);
    }
}

/**
 * @brief Helper function to get token at specific index
 */
t_token	*get_token_at_index(t_vector *vec, size_t index)
{
    if (!vec || !vec->array || index >= vec->nb_elements)
        return (NULL);
    return ((t_token *)((char *)vec->array + (index * vec->datatype_size)));
}

/**
 * @brief Initialize the s_input structure
 * @param input Pointer to the structure to initialize
 */
void	init_input(t_input *input)
{
    if (!input)
        return ;
    input->token_qty = 0;
    input->v_tokens = create_vector(5, sizeof(t_token), clear_token_content);
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
    if (!input)
        return (-1);
    init_input(input);
    if (!input->v_tokens)
        return (-1);
    
    // Pre-grow the vector if needed
    if (token_count > 0 && !grow_vector(input->v_tokens, token_count))
        return (-1);
    
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
        
        // Add token to vector
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
    if (!input || !input->v_tokens)
        return ;
    
    // The vector's clear_array function will handle freeing token content
    clear_vector(input->v_tokens);
    input->v_tokens = NULL;
    input->token_qty = 0;
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
    t_token	*token;

    for (size_t i = 0; i < input->token_qty; i++)
    {
        token = get_token_at_index(input->v_tokens, i);
        if (!token)
            continue;
            
        printf("'%s' : ", token->raw_content);
        switch (token->type)
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
        case APPEND:
            printf("APPEND\n");
            break ;
        case HEREDOC:
            printf("HEREDOC\n");
            break ;
        default:
            printf("type=%zd\n", token->type);
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