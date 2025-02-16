/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:38:34 by ruida-si          #+#    #+#             */
/*   Updated: 2025/02/13 18:39:35 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	exec_env(t_token *token, t_mini *mini)
{
	t_env	*ev;
	int		i;

	i = 0;
	ev = mini->envp;
	(void)token;
	while (ev)
	{
		if (!ev->content)
			printf("%s\n", ev->var);
		else
			printf("%s\n", ev->content);
		ev = ev->next;
		i++;
	}
	printf("%i\n", i);
}
// Destroy -u --unset Create VAR1=valor1 PATH=/custom/path ls