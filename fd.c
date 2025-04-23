/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:32:29 by marvin            #+#    #+#             */
/*   Updated: 2025/04/22 15:32:29 by marvin           ###   ########.fr       */
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

int handle_fd_input(char *file) 
{
    int fd_in = open(file, O_RDONLY);
    if (fd_in == -1)
        return -1;
    if (dup2(fd_in, 0) == -1) 
    {
        close(fd_in);
        return -1;
    }
    close(fd_in);
    return 0;
}

int handle_fd_output(char *file) 
{
    int fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_out == -1)
        return -1;
    if (dup2(fd_out, 1) == -1) 
    {
        close(fd_out);
        return -1;
    }
    close(fd_out);
    return 0;
}

int handle_fd_output_append(char *file) 
{
    int fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd_out == -1)
        return -1;
    if (dup2(fd_out, 1) == -1) 
    {
        close(fd_out);
        return -1;
    }
    close(fd_out);
    return 0;
}

int handle_fd_input_heredoc(char *word) 
{
    int fds[2];
    char *line;

    if (pipe(fds) == -1)
        return -1;
    while (1) 
    {
        line = readline("heredoc> ");
        if (!line || ft_strcmp(line, word) == 0) 
        {
            free(line);
            break;
        }
        write(fds[1], line, ft_strlen(line));
        write(fds[1], "\n", 1);
        free(line);
    }
    close(fds[1]);
    if (dup2(fds[0], 0) == -1) 
    {
        close(fds[0]);
        return -1;
    }
    close(fds[0]);
    return 0;
}

void apply_fd(t_env *cmds) 
{
    int i = 0;
    while (cmds->arg[i]) 
    {
        if ((ft_strcmp(cmds->arg[i], "<") == 0 ||
             ft_strcmp(cmds->arg[i], ">") == 0 ||
             ft_strcmp(cmds->arg[i], ">>") == 0 ||
             ft_strcmp(cmds->arg[i], "<<") == 0) && cmds->arg[i + 1]) 
        {
            if (ft_strcmp(cmds->arg[i], "<") == 0) 
            {
                if (handle_fd_input(cmds->arg[i + 1]) == -1)
                    perror("input redirection error");
            }
            else if (ft_strcmp(cmds->arg[i], ">") == 0) 
            {
                if (handle_fd_output(cmds->arg[i + 1]) == -1)
                    perror("output redirection error");
            }
            else if (ft_strcmp(cmds->arg[i], ">>") == 0) 
            {
                if (handle_fd_output_append(cmds->arg[i + 1]) == -1)
                    perror("append redirection error");
            }
            else if (ft_strcmp(cmds->arg[i], "<<") == 0) 
            {
                if (handle_fd_input_heredoc(cmds->arg[i + 1]) == -1)
                    perror("heredoc error");
            }

            remove_args(cmds->arg, i);
        } else {
            i++;
        }
    }
}
