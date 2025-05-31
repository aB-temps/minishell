#include "exec.h"



void	debug_print_token(t_token *token)
{
    if (token->type == COMMAND)
        printf("Commande trouvée: %s\n", token->raw_content);
    else if (token->type == PIPE)
        printf("Pipe trouvé\n");
    else if (token->type == REDIR_IN)
        printf("Redirection d'entrée: %s\n", token->raw_content);
    else if (token->type == REDIR_OUT)
        printf("Redirection de sortie: %s\n", token->raw_content);
    else if (token->type == ARG)
        printf("Argument: %s\n", token->raw_content);
}

void	handle_token(t_input *input, ssize_t i, char **env)
{
    t_token	*token;

    token = get_token_at_index(input->v_tokens, i);
    if (!token)
        return ;
    debug_print_token(token);
    (void)env;
}

void	debug_print_all_tokens(t_input *input, char **env)
{
    ssize_t	i;

    i = 0;
    printf("=== Analyse des tokens ===\n");
    while (i < input->token_qty)
    {
        handle_token(input, i, env);
        i++;
    }
    printf("=== Fin de l'analyse ===\n\n");
}
