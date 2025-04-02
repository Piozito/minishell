/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:30:04 by marvin            #+#    #+#             */
/*   Updated: 2025/04/02 15:03:23 by aaleixo-         ###   ########.fr       */
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
        {
            exit(1);
        }
        close(prev_fd);
    }
    if (!is_last) 
    {
        if (dup2(p_fd[1], STDOUT_FILENO) == -1) 
        {
            exit(1);
        }
        close(p_fd[1]);
    }
    close(p_fd[0]);
    check_builtin(cmd);
    exit(1);
}

static void handle_child_process(t_env *cmds, int prev_fd, int p_fd[2], int is_last) 
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0) 
    {
        execute_command(cmds, prev_fd, p_fd, is_last);
    }
}

static void handle_parent_process(int p_fd[2], int *prev_fd) 
{
    close(p_fd[1]);
    if (*prev_fd != 0) 
    {
        close(*prev_fd);
    }
    *prev_fd = p_fd[0];
}

void ft_pipe(t_env *cmds) 
{
    int prev_fd = 0;
    int p_fd[2];
    int num_cmds = 0;
    t_env *cmd;
	
	cmd = cmds;
    while (cmd) 
    {
        num_cmds++;
        cmd = cmd->next;
    }

    for (int i = 0; i < num_cmds; i++) 
    {
        if (i < num_cmds - 1) 
        {
            create_pipe(p_fd);
        } 
        else 
        {
            p_fd[0] = p_fd[1] = -1;
        }

        handle_child_process(cmds, prev_fd, p_fd, i == num_cmds - 1);

        if (i < num_cmds - 1) 
        {
            handle_parent_process(p_fd, &prev_fd);
        }

        cmds = cmds->next;
    }
    if (prev_fd != 0) 
    {
        close(prev_fd);
    }
    while (wait(NULL) > 0);
}