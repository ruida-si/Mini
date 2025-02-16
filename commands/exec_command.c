#include "./../minishell.h"

void exec_command(t_token *token)
{
    pid_t pid;
    int status;

    if (!token || !token->cmd)
        return;

    pid = fork();
    if (pid < 0)
    {
        perror("Erro ao criar processo");
        return;
    }
    if (pid == 0) // Processo filho (executa o comando)
    {
        signal(SIGINT, SIG_DFL);  // Restaurar comportamento padrão (Ctrl+C mata o processo)
        signal(SIGQUIT, SIG_DFL); // Restaurar comportamento padrão (Ctrl+\ exibe "Quit")
        
        execvp(token->cmd, token->args_file);
        perror("Erro ao executar comando");
        exit(127); // Código de erro padrão para comando não encontrado
    }
    else // Processo pai (Minishell)
    {
        signal(SIGINT, SIG_IGN); // Ignora Ctrl+C enquanto espera o filho
        signal(SIGQUIT, SIG_IGN); // Ignora Ctrl+\ enquanto espera o filho
        
        waitpid(pid, &status, 0);

        signal(SIGINT, sigint_handler); // Restaura handler para o Minishell
        signal(SIGQUIT, SIG_IGN); // Continua ignorando Ctrl+\ no shell
    }
}
