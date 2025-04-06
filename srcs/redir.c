/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:56:07 by marvin            #+#    #+#             */
/*   Updated: 2025/04/06 20:56:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int handle_redir_input(char *file, int *fd_in) 
{
    *fd_in = open(file, O_RDONLY);
    if (*fd_in == -1) 
    {
        return -1;
    }
    if (dup2(*fd_in, 0) == -1) 
    {
        close(*fd_in);
        return -1;
    }
    return 0;
}

int handle_redir_output(char *file, int *fd_out) 
{
    *fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (*fd_out == -1) 
    {
        return -1;
    }
    if (dup2(*fd_out, 1) == -1) 
    {
        close(*fd_out);
        return -1;
    }
    return 0;
}

int handle_redir_output_append(char *file, int *fd_out) 
{
    *fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
    if (*fd_out == -1)
        return -1;
    if (dup2(*fd_out, 1) == -1) 
    {
        close(*fd_out);
        return -1;
    }
    return 0;
}

int handle_redir_input_heredoc(char *word) 
{
    int fds[2];
    char buffer[1024];

    if (pipe(fds) == -1)
        return -1;
    while (1) 
    {
        write(1, "heredoc> ", 9);
        long bytes;

        bytes = read(1, buffer, 1024 - 1);
        if (bytes < 0)
        {
            close(fds[0]);
            close(fds[1]);
            return -1;
        }
        buffer[bytes] = '\0';
        char *newline = strchr(buffer, '\n');
        if (newline) 
            *newline = '\0';
        if (strcmp(buffer, word) == 0)
            break;
        write(fds[1], buffer, strlen(buffer));
        write(fds[1], "\n", 1);
    }
    close(fds[1]);
    dup2(fds[0], 0);
    close(fds[0]);
    return 0;
}

void apply_redirections(char **args, int *fd_in, int *fd_out) 
{
    int i;

    i = 0;
    while (args[i]) 
    {
        if ((strcmp(args[i], "<") == 0 || strcmp(args[i], ">") == 0 || 
        strcmp(args[i], ">>") == 0 || strcmp(args[i], "<<") == 0) && args[i + 1]) 
        {
            if (strcmp(args[i], "<") == 0)
                handle_redir_input(args[i + 1], fd_in);
            else if (strcmp(args[i], ">") == 0)
                handle_redir_output(args[i + 1], fd_out);
            else if (strcmp(args[i], ">>") == 0)
                handle_redir_output_append(args[i + 1], fd_out);
            else if (strcmp(args[i], "<<") == 0)
                handle_redir_input_heredoc(args[i + 1], fd_in, 1);
            args[i] = NULL;
            args[i + 1] = NULL;
        }
        i++
    }
}