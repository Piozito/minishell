/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:26:00 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/04 13:15:27 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	cmd_check(t_env *cmds)
{
	if (cmds->cmd == NULL)
		return (1);
	else if (ft_strstr(cmds->cmd, "echo") != NULL)
		return (0);
	else if (ft_strstr(cmds->cmd, "pwd") != NULL)
		return (0);
	else if (ft_strstr(cmds->cmd, "cd") != NULL)
		return (0);
	else if (ft_strstr(cmds->cmd, "env") != NULL)
		return (0);
	else if (ft_strstr(cmds->cmd, "exit") != NULL)
		return (0);
	else if (ft_strstr(cmds->cmd, "unset") != NULL)
		return (0);
	else if (ft_strstr(cmds->cmd, "export") != NULL)
		return (0);
	if (cmds->path == NULL)
	{
		cmds->exit_status = 127;
		return (1);
	}
	else
		return (2);
	return (0);
}

void	malloc_fail(char **tokens)
{
	int	i;

	i = 0;
	if (tokens && tokens[0] != NULL)
	{
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
	}
	ft_putstr_fd("Malloc allocation failed.\n", 2);
	exit(1);
}

void	set_args(t_env *cmd, char **subtokens, int command_set)
{
	int	j;
	int	arg_index;

	j = 0;
	arg_index = 0;
	while (subtokens[j])
	{
		if (j == command_set)
			cmd->cmd = ft_strdup(subtokens[j]);
		else if (j < command_set)
			cmd->arg[arg_index++] = ft_strdup(subtokens[j]);
		j++;
	}
	j = command_set + 1;
	while (j > command_set && subtokens[j])
	{
		cmd->arg[arg_index++] = ft_strdup(subtokens[j]);
		j++;
	}
	cmd->arg[arg_index] = NULL;
}

int	is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_separator(char ch, char c, int quote, int dquote)
{
	if (c == ' ')
		return (!quote && !dquote && (ch == c || ch == '\t' || ch == '\0'));
	return (!quote && !dquote && (ch == c || ch == '\0'));
}
