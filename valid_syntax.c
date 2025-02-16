#include "minishell.h"

static int validate_pipe_syntax(t_token *tokens) {
    t_token *current = tokens;
    int pipe_count = 0;
    
    if (current && current->type == CMD_PIPE)
        return 0;
        
    while (current) {
        if (current->type == CMD_PIPE) {
            pipe_count++;
            if (!current->prev || !current->next || 
                current->prev->type == CMD_PIPE ||
                current->next->type == CMD_PIPE)
                return 0;
            
            if (current->next->type != CMD_EXEC && 
                current->next->type != CMD_BUILDIN)
                return 0;
        }
        current = current->next;
    }
    
    return 1;
}

static int validate_redirect_syntax(t_token *tokens) {
    t_token *current = tokens;
    
    while (current) {
        if (current->type == CMD_REDIRECT) {
            if (!current->next || current->next->type != CMD_ARG_FILE)
                return 0;
                
            if (current->prev && current->prev->type == CMD_REDIRECT)
                return 0;
                
            if (!current->prev || 
                (current->prev->type != CMD_EXEC && 
                 current->prev->type != CMD_BUILDIN && 
                 current->prev->type != CMD_ARG))
                return 0;
        }
        current = current->next;
    }
    return 1;
}

static int validate_command_sequence(t_token *tokens) {
    t_token *current = tokens;
    int exec_count = 0;
    
    while (current) {
        if (current->type == CMD_EXEC || current->type == CMD_BUILDIN)
            exec_count++;
            
        if (current->type == CMD_PIPE) {
            if (!current->next || 
                (current->next->type != CMD_EXEC && 
                 current->next->type != CMD_BUILDIN))
                return 0;
        }
        current = current->next;
    }
    
    return exec_count > 0;
}

static int validate_syntax(t_mini *ms) {
    if (!ms || !ms->token)
        return 0;
        
    return (validate_pipe_syntax(ms->token) &&
            validate_redirect_syntax(ms->token) &&
            validate_command_sequence(ms->token));
}

void handle_syntax_error(t_mini *ms) {
    if (!validate_syntax(ms)) {
        fprintf(stderr, "minishell: syntax error\n");
        ms->token = NULL;
    }
}