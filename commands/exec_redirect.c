#include "./../minishell.h"

void exec_redirect(t_token *token)
{
    int fd;
    
    if (!token->args_file[0])
        return;

    if (strcmp(token->cmd, ">") == 0)
        fd = open(token->args_file[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (strcmp(token->cmd, ">>") == 0)
        fd = open(token->args_file[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (strcmp(token->cmd, "<") == 0)
        fd = open(token->args_file[0], O_RDONLY);
    
    if (fd < 0) {
        perror("Erro ao abrir arquivo");
        return;
    }
    
    if (strcmp(token->cmd, "<") == 0)
        dup2(fd, STDIN_FILENO);
    else
        dup2(fd, STDOUT_FILENO);
    
    close(fd);
}