/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:31:57 by ruida-si          #+#    #+#             */
/*   Updated: 2025/02/12 16:00:28 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	update_var(char *oldpwd, char *pwd, t_mini *mini)
{
	t_env	*ev;

	ev = mini->envp;
	while (ev)
	{
		if (ft_strcmp(ev->var, "OLDPWD") == 0)
		{
			ev->content = ft_strjoin("OLDPWD=", oldpwd);
		}
		else if (ft_strcmp(ev->var, "PWD") == 0)
		{
			ev->content = ft_strjoin("PWD=", pwd);
		}
		ev = ev->next;
	}
}

char	*expand_var(char *var, t_env *ev)
{
	int		i;
	char	*content;

	i = ft_strlen(var) + 1;
	content = NULL;
	while (ev)
	{
		if (ft_strcmp(ev->var, var) == 0)
		{
			if (ev->content)
				content = ft_strdup(ev->content + i);
			break ;
		}
		ev = ev->next;
	}
	return (content);
}

void	free_pwd(char *oldpwd, char *pwd)
{
	if (oldpwd)
		free(oldpwd);
	if (pwd)
		free(pwd);
}

char	*get_new_cwd(char *buffer)
{
	int		i;
	char	*new;

	new = ft_strdup(buffer);
	i = ft_strlen(new) - 1;
	while (i >= 0)
	{
		if (new[i] == '/')
		{
			if (i == 0)
				new[++i] = '\0';
			else
				new[i] = '\0';
			break ;
		}
		i--;
	}
	return (new);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
	{
		printf("Error strcmp: NULL string");
		return (1);
	}
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
