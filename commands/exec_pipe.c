#include "./../minishell.h"

void exec_pipe(t_token *token)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("Erro ao criar pipe");
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execvp(token->cmd, token->args_file);
        perror("Erro ao executar comando");
        exit(1);
    }
    else
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        waitpid(pid, NULL, 0);
    }
}
