#include "minishell.h"

void free_tokens(t_token *token)
{
    t_token *tmp;

    while (token)
    {
        tmp = token->next;
        if (token->cmd)
            free(token->cmd);
        if (token->args_file)
        {
            for (int i = 0; token->args_file[i]; i++)
                free(token->args_file[i]);
            free(token->args_file);
        }
        free(token);
        token = tmp;
    }
}
