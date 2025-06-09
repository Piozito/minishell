/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:49:43 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/09 16:00:19 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

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
		write(1, "Quit (core dumped)\n", 19);
	}
	else if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ft_fake_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		(void)sig;
	}
	else if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	general_error(char *str, int free, int ex, t_env *cmds)
{
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	if (ex == 1)
	{
		ft_clear(cmds);
		exit(1);
	}
	if (free == 1)
		ft_cmds_free(cmds, 0);
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
