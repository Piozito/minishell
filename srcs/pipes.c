/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:30:04 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 13:52:05 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	execute_command(t_env *cmd, int prev_fd, int p_fd[2], int is_last)
{
	if (prev_fd != 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			exit(1);
		close(prev_fd);
	}
	if (!is_last)
	{
		if (dup2(p_fd[1], STDOUT_FILENO) == -1)
			exit(1);
		close(p_fd[1]);
	}
	if (apply_fd(cmd) == 1)
		exit(1);
	cmd->exit_status = check_builtin(cmd);
	duping(cmd);
	exit(cmd->exit_status);
}

pid_t	handle_child(t_env *cmds, int prev_fd, int p_fd[2], int is_last)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		if ((ft_isalpha(cmds->cmd[0]) == 0 && cmd_check(cmds) == 0)
			|| cmds->cmd[0] == ' ')
		{
			command_not_found(cmds->cmd);
			exit(127);
		}
		execute_command(cmds, prev_fd, p_fd, is_last);
	}
	return (pid);
}

void	handle_parent_process(int p_fd[2], int *prev_fd)
{
	close(p_fd[1]);
	if (*prev_fd != 0)
		close(*prev_fd);
	*prev_fd = p_fd[0];
}

int	ft_pipe(t_env *cmds)
{
	int		num_cmds;
	pid_t	last_pid;
	t_env	*cmd;

	num_cmds = 0;
	last_pid = -1;
	if (cmds == NULL)
	{
		printf("Error: cmds is NULL\n");
		return (1);
	}
	cmd = cmds;
	while (cmd)
	{
		num_cmds++;
		cmd = cmd->next;
	}
	cmd = cmds;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	pipo(cmd, num_cmds, &last_pid);
	signal(SIGINT, ft_noint_handler);
	signal(SIGQUIT, ft_noint_handler);
	return (wait_for_it(last_pid));
}
