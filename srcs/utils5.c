/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:17:27 by fragarc2          #+#    #+#             */
/*   Updated: 2025/05/22 15:46:51 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void remove_args(char **args, int pos)
{
    int j = pos;
    while (args[j + 2])
    {
        args[j] = args[j + 2];
        j++;
    }
    args[j] = NULL;
    args[j + 1] = NULL;
}

void create_pipe(int p_fd[2])
{
    if (pipe(p_fd) == -1)
    {
        perror("pipe");
        exit(1);
    }
}

int wait_for_it(pid_t last_pid)
{
	int exit_code;
	int status = 0;
	pid_t wpid;

	status = 0;
	exit_code = 0;
    while ((wpid = wait(&status)) > 0)
	{
        if (wpid == last_pid)
		{
            if (WIFEXITED(status))
                exit_code = WEXITSTATUS(status);
            else
                exit_code = 1;
        }
    }
    return exit_code;
}

void pipo(t_env *cmd, int num_cmds, pid_t last_pid)
{
	int i;
	int p_fd[2];
	int prev_fd;

	prev_fd = 0;
	i = 0;
	 while (i < num_cmds)
	{
        if (i < num_cmds - 1)
            create_pipe(p_fd);
        else
            p_fd[0] = p_fd[1] = -1;
        pid_t pid = handle_child_process(cmd, prev_fd, p_fd, i == num_cmds - 1);
        if (i == num_cmds - 1)
            last_pid = pid;
        if (i < num_cmds - 1)
            handle_parent_process(p_fd, &prev_fd);
        cmd = cmd->next;
        i++;
    }
	if (prev_fd != 0)
        close(prev_fd);
}
