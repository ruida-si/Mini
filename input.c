#include "minishell.h"

char *get_input(t_mini *ms, char *prompt)
{
    char *input;
    (void)ms;
    input = readline(prompt);
    if (!input)
    {
        write(STDOUT_FILENO, "exit\n", 5);
        exit(0);
    }
    if (input && *input)
        add_history(input);
    return input;
}

void    sigint_handler(int sig)
{
    (void)sig;
    if (isatty(STDIN_FILENO))
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void    sigquit_handler(int sig)
{
    (void)sig;
}

void    setup_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
}