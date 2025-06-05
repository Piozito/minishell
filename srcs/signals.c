/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:49:43 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/05 19:21:30 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_cmds_free(t_env *cmds)
{
	t_env	*temp;
	t_env	*next;

	if (!cmds)
		return ;
	if (cmds->cmd && (!cmds->path || ft_strcmp(cmds->cmd, cmds->path) != 0))
		free(cmds->cmd);
	if (cmds->path)
		free(cmds->path);
	free_subtokens(cmds->arg);
	temp = cmds->next;
	while (temp != NULL)
	{
		next = temp->next;
		if (temp->cmd && (!temp->path || ft_strcmp(temp->cmd, temp->path) != 0))
			free(temp->cmd);
		if (temp->path)
			free(temp->path);
		free_subtokens(temp->arg);
		free(temp);
		temp = next;
	}
	cmds->next = NULL;
}

void	ft_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	ft_noint_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		if (isatty(0))
			write(1, "Quit (core dumped)\n", 19);
	}
	else if (sig == SIGINT)
	{
		if (isatty(0))
			write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	general_error(char *str, int free, int ex, t_env *cmds)
{
	if (free == 1)
		ft_clear(cmds);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	if (ex == 1)
		exit(1);
	return (1);
}

int	check_builtin(t_env *cmds)
{
	if (cmds->cmd == NULL)
		return (127);
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		return (ft_echo(cmds));
	else if (ft_strcmp(cmds->cmd, "pwd") == 0)
		return (ft_pwd(cmds));
	else if (ft_strcmp(cmds->cmd, "cd") == 0)
		return (ft_cd(cmds));
	else if (ft_strcmp(cmds->cmd, "env") == 0)
		return (ft_env(cmds));
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		return (ft_exit(cmds));
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		return (ft_unset(cmds));
	else if (ft_strcmp(cmds->cmd, "export") == 0)
		return (ft_export(cmds));
	else
		return (ft_exec(cmds));
}
