/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:30:00 by enchevri          #+#    #+#             */
/*   Updated: 2025/06/05 15:30:00 by enchevri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_string_array(char **array, const char *array_name)
{
	int	i;

	if (!array)
	{
		printf("DEBUG: %s = NULL\n", array_name);
		return ;
	}
	
	printf("DEBUG: %s @ %p:\n", array_name, (void *)array);
	i = 0;
	while (array[i])
	{
		printf("  [%d] = \"%s\" @ %p\n", i, array[i], (void *)array[i]);
		i++;
	}
	printf("  [%d] = NULL (end)\n", i);
	printf("  Total elements: %d\n\n", i);
}

/**
 * Affiche tous les tokens et leurs formatted_content
 */
void	print_all_tokens(t_input *input)
{
	int		i;
	t_token	*tokens_array;
	t_token	*current_token;
	char	*type_names[] = {
		"COMMAND", "ARG", "PIPE", "REDIR_IN", "REDIR_OUT", 
		"APPEND", "HEREDOC", "ASSIGN", "S_QUOTES", "D_QUOTES", "ENV_VAR"
	};

	if (!input || !input->v_tokens)
	{
		printf("DEBUG: Input or v_tokens is NULL\n");
		return ;
	}

	printf("=== DEBUG: ALL TOKENS ===\n");
	printf("Token quantity: %zd\n", input->token_qty);
	printf("Vector @ %p, array @ %p\n\n", 
		   (void *)input->v_tokens, (void *)input->v_tokens->array);

	tokens_array = (t_token *)input->v_tokens->array;
	
	for (i = 0; i < input->token_qty; i++)
	{
		current_token = &tokens_array[i];
		
		printf("--- TOKEN [%d] ---\n", i);
		printf("Address: %p\n", (void *)current_token);
		printf("Type: %s (%zd)\n", 
			   (current_token->type >= 0 && current_token->type <= 10) ? 
			   type_names[current_token->type] : "UNKNOWN", 
			   current_token->type);
		printf("Raw content: \"%s\" @ %p\n", 
			   current_token->raw_content ? current_token->raw_content : "NULL",
			   (void *)current_token->raw_content);
		
		// Afficher formatted_content selon le type
		if (current_token->formatted_content)
		{
			if (current_token->type == COMMAND || current_token->type == ARG)
			{
				// C'est probablement un char **
				char **args = (char **)current_token->formatted_content;
				char array_name[64];
				snprintf(array_name, sizeof(array_name), "Token[%d].formatted_content", i);
				print_string_array(args, array_name);
			}
			else
			{
				printf("Formatted content: %p (type unknown, not displayed)\n", 
					   current_token->formatted_content);
			}
		}
		else
		{
			printf("Formatted content: NULL\n");
		}
		printf("\n");
	}
	printf("=== END DEBUG TOKENS ===\n\n");
}

/**
 * Affiche les variables d'environnement
 */
void	print_env_array(char **env)
{
	print_string_array(env, "Environment variables");
}

/**
 * Affiche un tableau d'entiers (comme les PIDs)
 */
void	print_int_array(int *array, int size, const char *array_name)
{
	int	i;

	if (!array)
	{
		printf("DEBUG: %s = NULL\n", array_name);
		return ;
	}
	
	printf("DEBUG: %s @ %p:\n", array_name, (void *)array);
	for (i = 0; i < size; i++)
	{
		printf("  [%d] = %d\n", i, array[i]);
	}
	printf("  Total elements: %d\n\n", size);
}

/**
 * Fonction principale de debug - affiche tout
 */
void	debug_print_all_arrays(t_input *input, int *pids, int pid_count)
{
	printf("\n========================================\n");
	printf("         DEBUG: ALL ARRAYS\n");
	printf("========================================\n\n");
	
	// Afficher tous les tokens
	print_all_tokens(input);
	
	// Afficher les PIDs si fournis
	if (pids && pid_count > 0)
		print_int_array(pids, pid_count, "Process PIDs");
	
	// Afficher l'environnement (optionnel, peut être très long)
	printf("Environment variables available (use print_env_array(env) to see them)\n\n");
	
	printf("========================================\n");
	printf("       END DEBUG: ALL ARRAYS\n");
	printf("========================================\n\n");
}

/**
 * Version simplifiée pour débugger rapidement un token spécifique
 */
void	debug_single_token(t_input *input, int token_index)
{
	t_token	*tokens_array;
	t_token	*token;
	char	array_name[64];

	if (!input || !input->v_tokens || token_index >= input->token_qty)
	{
		printf("DEBUG: Invalid input or token index\n");
		return ;
	}

	tokens_array = (t_token *)input->v_tokens->array;
	token = &tokens_array[token_index];

	printf("=== DEBUG: TOKEN [%d] ===\n", token_index);
	printf("Raw: \"%s\"\n", token->raw_content ? token->raw_content : "NULL");
	
	if (token->formatted_content && 
		(token->type == COMMAND || token->type == ARG))
	{
		snprintf(array_name, sizeof(array_name), "Token[%d].formatted_content", token_index);
		print_string_array((char **)token->formatted_content, array_name);
	}
	printf("=== END DEBUG TOKEN ===\n\n");
}
