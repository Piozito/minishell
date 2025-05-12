/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:30:04 by marvin            #+#    #+#             */
/*   Updated: 2025/05/12 12:36:47 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"


static void create_pipe(int p_fd[2])
{
    if (pipe(p_fd) == -1)
    {
        perror("pipe");
        exit(1);
    }
}

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
	apply_fd(cmd);
    exit(check_builtin(cmd));
}


static pid_t handle_child_process(t_env *cmds, int prev_fd, int p_fd[2], int is_last)
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
			printf("command not found: \"%s\"\n", cmds->cmd);
			exit(127);
		}
        execute_command(cmds, prev_fd, p_fd, is_last);
	}
	return pid;
}

static void handle_parent_process(int p_fd[2], int *prev_fd)
{
    close(p_fd[1]);
    if (*prev_fd != 0)
        close(*prev_fd);
    *prev_fd = p_fd[0];
}

int ft_pipe(t_env *cmds)
{
    int prev_fd = 0;
    int p_fd[2];
    int num_cmds = 0;
	int status = 0;
	int exit_code = 0;
	int i;
	pid_t last_pid = -1;
    t_env *cmd;

	i = 0;
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
    while (i < num_cmds)
	{
		if (cmd_check(cmds) == 0 && num_cmds == 1)
    		return check_builtin(cmds);
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
    pid_t wpid;
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