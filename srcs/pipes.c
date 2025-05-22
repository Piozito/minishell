/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:30:04 by marvin            #+#    #+#             */
/*   Updated: 2025/05/22 15:45:21 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void execute_command(t_env *cmd, int prev_fd, int p_fd[2], int is_last)
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
	if(apply_fd(cmd) == 1)
		exit(1);
	cmd->exit_status = check_builtin(cmd);
	duping(cmd);
    exit(cmd->exit_status);
}


pid_t handle_child_process(t_env *cmds, int prev_fd, int p_fd[2], int is_last)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
	{
		if((ft_isalpha(cmds->cmd[0]) == 0 && cmd_check(cmds) == 0) || cmds->cmd[0] == ' ')
		{
			command_not_found(cmds->cmd);
			exit(127);
		}
        execute_command(cmds, prev_fd, p_fd, is_last);
	}
	return pid;
}

void handle_parent_process(int p_fd[2], int *prev_fd)
{
    close(p_fd[1]);
    if (*prev_fd != 0)
        close(*prev_fd);
    *prev_fd = p_fd[0];
}

int ft_pipe(t_env *cmds)
{
    int num_cmds = 0;
	pid_t last_pid = -1;
    t_env *cmd;

    if (cmds == NULL)
	{
        printf("Error: cmds is NULL\n");
        return 1;
    }
    cmd = cmds;
    while (cmd)
    {
        num_cmds++;
        cmd = cmd->next;
    }
    cmd = cmds;
   	pipo(cmd, num_cmds, last_pid);
    return (wait_for_it(last_pid));
}
