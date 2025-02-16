/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:37:34 by ruida-si          #+#    #+#             */
/*   Updated: 2025/02/16 18:45:44 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

int		check_syntax(char *cmd);
int		check_alpha(int	*i, char *cmd);
void	create_export(char *var, char *content, t_mini *mini);
void	export_one(char *input, int *i, int j, t_mini *mini);
void	export_two(char *input, int *i, int j, t_mini *mini);
void	export_quotes(char *input, int *i, int j, t_mini *mini);

void	exec_export(t_token *token, t_mini *mini)
{
	char	*input;
	int		i;
	int		j;

	i = 0;
	order_var(mini);
	if (!token->next)
		print_export(mini->export);
	else if (!check_syntax(mini->input + 7))
		return ;
	else
	{
		input = mini->input + 7;
		while (input[i])
		{
			j = i;
			while (input[i] && input[i] != '=' && input[i] != ' ')
				i++;
			if (!input[i] || input[i] == ' ')
				export_one(input, &i, j, mini);
			else if (input[i]  == '=')
				export_two(input, &i, j, mini);
		}			
	}
}

void	export_quotes(char *input, int *i, int j, t_mini *mini)
{
	char	*var;
	char	*content;
	char	*temp;
	int		a;

	a = 0;
	var = ft_strdup(&input[j]);
	while (var[a] && var[a] != '=')
		a++;
	var[a] = '\0';
	content = ft_strdup(&input[*i]);
	a = 0;
	while (content[a] && content[a] != '\'' && content[a] != '\"')
		a++;
	content[a] = '\0';
	temp = ft_strjoin("=", content);
	free(content);
	content = ft_strjoin(var, temp);
	create_export(var, content, mini);	
	while (input[*i] && input[*i] != '\'' && input[*i] != '\"')
		(*i)++;
	if (input[*i])
		(*i)++;
	if (input[*i])
		(*i)++;
}

void	export_two(char *input, int *i, int j, t_mini *mini)
{
	char	*var;
	char	*content;
	int		a;

	if (input[*i + 1] == '\'' || input[*i + 1] == '\"')
	{
		(*i) += 2;
		export_quotes(input, i, j, mini);
		return ;		
	}
	a = 0;
	var = ft_strdup(&input[j]);
	while (var[a] && var[a] != '=')
		a++;
	var[a] = '\0';
	content = ft_strdup(&input[j]);
	a = 0;
	while (content[a] && content[a] != ' ')
		a++;
	content[a] = '\0';
	create_export(var, content, mini);
	while (input[*i] && input[*i] != ' ')
		(*i)++;
	if (input[*i])
		(*i)++;		
}

void	export_one(char *input, int *i, int j, t_mini *mini)
{
	char	*var;
	int		a;

	a = 0;
	var = ft_strdup(&input[j]);
	while (var[a] && var[a] != ' ')
		a++;		
	var[a] = '\0';
	create_export(var, NULL, mini);
	if (input[*i])
		(*i)++;	
}

void	create_export(char *var, char *content, t_mini *mini)
{
	t_env	*export;
	t_env	*env;
	
	export = find_node(var, mini->export);
	env = find_node(var, mini->envp);
	if (export)
	{
		if (content)
		{
			free(export->content);
			export->content = content;
			if (!env)
				append_node(var, content, mini->envp);
			else
			{
				/* if (env->content)
					free(env->content); */
				env->content = content;
			}
		}
		return ;
	}
	append_node(var, content, mini->export);
	if (content)
		append_node(var, content, mini->envp);
}

int	check_syntax(char *cmd)
{
	int	i;

	i = 0;
	if (ft_isdigit(cmd[0]) || !check_alpha(&i, cmd))
	{
		if (i != 0)
		{
			while (cmd[i] != ' ' && i >= 0)
				i--;
			i++;
		}
		printf("minishell: export: `%s': not a valid identifier\n", cmd + i);
		return (0);
	}
	return (1);
}

int	check_alpha(int	*i, char *cmd)
{
	int	j;
	
	j = 1;
	while (cmd[*i])
	{
		if (cmd[*i] == '=')
		{
			j *= -1;
			(*i)++;
		}
		if (j == 1)
		{
			if (!cmd[*i])
				break ;
			if (cmd[*i] != '=' && cmd[*i] != '\"' && cmd[*i] != ' '
					&& cmd[*i] != '\'' && !ft_isalnum(cmd[*i]))
				return (0);
		}
		(*i)++;
	}
	return (1);
}
