/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:30:04 by marvin            #+#    #+#             */
/*   Updated: 2025/03/31 13:30:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void create_pipe(int p_fd[2])
{
    if (pipe(p_fd) == -1) 
        exit(1);
}

static void execute_command(char *cmd, int prev_fd, int p_fd[2], int is_last)
{
    if (prev_fd != 0) 
    {
        dup2(prev_fd, 0);
        close(prev_fd);
    }
    if (!is_last) 
    {
        dup2(p_fd[1], 1);
        close(p_fd[1]);
    }
    close(p_fd[0]);

    char *argv[] = {cmd, NULL};
    execve(cmd, argv, NULL);
    exit(1);
}

static void handle_child_process(char *cmd, int prev_fd, int p_fd[2], int is_last)
{
    pid_t pid = fork();
    if (pid == -1) 
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0) 
    {
        execute_command(cmd, prev_fd, p_fd, is_last);
    }
}

static void handle_parent_process(int p_fd[2], int *prev_fd)
{
    close(p_fd[1]);
    if (*prev_fd != 0)
        close(*prev_fd);
    *prev_fd = p_fd[0];
}

void ft_pipe(t_env *cmds)
{
    int prev_fd = 0;
    int p_fd[2];
    int num_cmds;
    int i;

    i = 0;
    num_cmds = ft_lstsize(cmds);
    while ( i < num_cmds) 
    {
        if (i < num_cmds - 1)
            create_pipe(p_fd);
        handle_child_process(cmds->arg, prev_fd, p_fd, i == num_cmds - 1); 
        if (i < num_cmds - 1)
            handle_parent_process(p_fd, &prev_fd);
        cmds = cmds->next;
        i++;
    }
    
    while (wait(NULL) > 0);
}
