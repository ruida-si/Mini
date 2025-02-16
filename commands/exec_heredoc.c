#include "./../minishell.h"

void exec_heredoc(t_token *token)
{
    char buffer[1024];

    printf("Digite o texto (Ctrl+D para sair):\n");
    
    while (1)
    {
        printf("> ");
        fgets(buffer, 1024, stdin);
        
        if (strcmp(buffer, token->args_file[0]) == 0)
            break;

        printf("%s", buffer);
    }
}
