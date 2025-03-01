/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:36:36 by ruida-si          #+#    #+#             */
/*   Updated: 2025/03/01 13:59:01 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	free_node(t_env *temp);
void	delete_node(t_env *prev, t_env *next);
void	unset_env(t_token *next, t_env **head);

void	exec_unset(t_token *token, t_mini *mini)
{
	t_token	*next;

	next = token->next;
	if (!next)
		return ;
	while (next)
	{
		unset_env(next, &mini->export);
		next = next->next;
	}
}

void	unset_env(t_token *next, t_env **head)
{
	t_env	*ev;

	ev = *head;
	while (ev)
	{
		if (ft_strcmp(ev->var, next->cmd) == 0)
		{
			if (ev == *head)
				*head = ev->next;
			delete_node(ev->prev, ev->next);
			free_node(ev);
			break ;
		}
		ev = ev->next;
	}
}

void	delete_node(t_env *prev, t_env *next)
{
	if (prev && next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (!prev)
		next->prev = NULL;
	else if (!next)
		prev->next = NULL;
}

void	free_node(t_env *temp)
{
	if (temp->var)
	{
		free(temp->var);
		temp->var = NULL;
	}
	if (temp->content)
	{
		free(temp->content);
		temp->content = NULL;
	}
	free(temp);
}
