/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:24:47 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/09 12:08:33 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*shlvl_setter(char *env, int *num)
{
	char	*str;
	char	*res;

	str = ft_strtrim(ft_strchr(env, '='), "=");
	(*num) = ft_atoi(str);
	free(str);
	if ((*num) < 0)
		(*num) = 0;
	else
		(*num)++;
	str = ft_itoa((*num));
	res = ft_strjoin("SHLVL=", str);
	free(str);
	return (res);
}

void	check_shlvl(char **new_environ, char **environ, int count)
{
	int		i;
	int		num;

	num = -1;
	i = -1;
	while (++i < count)
	{
		if (ft_strncmp(environ[i], "SHLVL=", 6) == 0)
			new_environ[i] = shlvl_setter(environ[i], &num);
		else
			new_environ[i] = ft_strdup(environ[i]);
	}
	if (num == -1)
		new_environ[i++] = ft_strdup("SHLVL=1");
	new_environ[i] = NULL;
}

char	**deep_copy_environ(char **environ)
{
	char	**new_environ;
	int		count;
	int		num;

	num = -1;
	count = 0;
	while (environ[count] != NULL)
		count++;
	if (count == 0)
		new_environ = fake_env_creator();
	else
	{
		new_environ = (char **)malloc((count + 2) * sizeof(char *));
		if (!new_environ)
			general_error("env malloc failed.", 0, 1, NULL);
		check_shlvl(new_environ, environ, count);
	}
	return (new_environ);
}

void	initialize_cmd(t_env *cmd, t_env *new_cmd, int i)
{
	if (new_cmd == NULL && i == 1)
	{
		cmd->cmd = NULL;
		cmd->path = NULL;
		cmd->arg = NULL;
		cmd->prev = NULL;
		cmd->next = NULL;
		cmd->heredoc = -1;
		cmd->saved_stds[0] = dup(0);
		cmd->saved_stds[1] = dup(1);
		return ;
	}
	new_cmd->env = cmd->env;
	new_cmd->exp = cmd->exp;
	new_cmd->saved_stds[0] = cmd->saved_stds[0];
	new_cmd->saved_stds[1] = cmd->saved_stds[1];
	new_cmd->path = NULL;
	new_cmd->cmd = NULL;
	new_cmd->arg = NULL;
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	new_cmd->exit_status = cmd->exit_status;
	new_cmd->heredoc = cmd->heredoc;
}

void	free_subtokens(char **subtokens)
{
	int	i;

	i = 0;
	if (!subtokens)
		return ;
	while (subtokens[i] != NULL)
	{
		if (subtokens[i])
			free(subtokens[i]);
		i++;
	}
	if (subtokens)
		free(subtokens);
}
