/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:36:36 by ruida-si          #+#    #+#             */
/*   Updated: 2025/02/15 17:12:14 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	free_node(t_env *temp);
void	delete_node(t_env *prev, t_env *next, t_env **head);
void	unset_env(t_token *next, t_env **head);

void	exec_unset(t_token *token, t_mini *mini)
{	
	t_token	*next;

	next = token->next;
	if (!next)
		return ;
	unset_env(next, &mini->envp);
	unset_env(next, &mini->export);
}

void	unset_env(t_token *next, t_env **head)
{
	t_env	*ev;
	
	ev = *head;
	while (next)
	{
		while (ev)
		{
			if (ft_strcmp(ev->var, next->cmd) == 0)
			{
				delete_node(ev->prev, ev->next, head);
				free_node(ev);
				ev = *head;
				break ;
			}
			ev = ev->next;
		}
		next = next->next;
	}	
}

void	delete_node(t_env *prev, t_env *next, t_env **head)
{
	(void)head;
	if (prev && next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (!prev)
	{
		next->prev = NULL;
		*head = next;
	}
	else if (!next)
		prev->next = NULL;
}

void	free_node(t_env *temp)
{
	if (temp->var)
		free(temp->var);
	free(temp);
}
