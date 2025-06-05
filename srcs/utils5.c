/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:17:27 by fragarc2          #+#    #+#             */
/*   Updated: 2025/06/05 19:27:48 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	remove_args(char **args, int pos)
{
	int	j;

	j = pos;
	free(args[j]);
	free(args[j + 1]);
	while (args[j + 2])
	{
		args[j] = args[j + 2];
		j++;
	}
	args[j] = NULL;
	args[j + 1] = NULL;
}

void	create_pipe(int p_fd[2])
{
	if (pipe(p_fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
}

int	wait_for_it(pid_t last_pid)
{
	int		exit_code;
	int		status;
	pid_t	wpid;

	status = 0;
	exit_code = 0;
	wpid = 1;
	while (wpid > 0)
	{
		wpid = wait(&status);
		if (wpid == last_pid)
			exit_code = WEXITSTATUS(status);
	}
	return (exit_code);
}

void	pipo(t_env *cmd, int num_cmds, pid_t *last_pid)
{
	int		i;
	int		p_fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = 0;
	i = -1;
	while (++i < num_cmds)
	{
		if (i < num_cmds - 1)
			create_pipe(p_fd);
		else
		{
			p_fd[0] = -1;
			p_fd[1] = -1;
		}
		pid = handle_child(cmd, prev_fd, p_fd, i == num_cmds - 1);
		if (i == num_cmds - 1)
			(*last_pid) = pid;
		if (i < num_cmds - 1)
			handle_parent_process(p_fd, &prev_fd);
		cmd = cmd->next;
	}
	if (prev_fd != 0)
		close(prev_fd);
}

int	arg_counter(char **subtokens, int *command_set)
{
	int	arg_count;
	int	j;
	int	k;

	j = 0;
	arg_count = 0;
	while (subtokens[j])
	{
		k = 0;
		command_finder(subtokens, command_set);
		while (subtokens[j][k])
		{
			if (subtokens[j][k] == '<' || subtokens[j][k] == '>')
				break ;
			k++;
		}
		arg_count++;
		j++;
	}
	return (arg_count);
}
