/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:24:18 by ruida-si          #+#    #+#             */
/*   Updated: 2025/02/13 18:40:49 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	swap_var(t_env *current, t_env *next, t_env **head);

void	append_node(char *var, char *content, t_env *head)
{
	t_env	*node;
	t_env	*last;

	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->content = content;
	node->var = var;
	node->next = NULL;
	last = ft_last(head);
	node->prev = last;
	last->next = node;
}

void	order_var(t_mini *mini)
{
	t_env	*head;
	t_env	*current;

	head = mini->export;
	current = head;
	while (current && current->next)
	{
		if (ft_strcmp(current->var, current->next->var) > 0)
		{
			swap_var(current, current->next, &head);
			current = head;
		}
		else
			current = current->next;
	}
	mini->export = head;
}

void	swap_var(t_env *current, t_env *next, t_env **head)
{
	if (*head == current)
		*head = next;
	if (current->prev)
	{
		current->prev->next = next;
		next->prev = current->prev;
	}
	else
		next->prev = NULL;
	if (next->next)
	{
		next->next->prev = current;
		current->next = next->next;
	}
	else
		current->next = NULL;
	next->next = current;
	current->prev = next;
}
