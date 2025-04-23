/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:56:07 by marvin            #+#    #+#             */
/*   Updated: 2025/04/23 15:47:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int handle_redir_input(char *file, int *fd_in)
{
	*fd_in = open(file, O_RDONLY);
	if (*fd_in == -1)
		return -1;

	if (dup2(*fd_in, 0) == -1)
	{
		close(*fd_in);
		return -1;
	}
	close(*fd_in);
	return 0;
}

int handle_redir_output(char *file, int *fd_out)
{
	*fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if (*fd_out == -1)
		return -1;

	if (dup2(*fd_out, 1) == -1)
	{
		close(*fd_out);
		return -1;
	}
	close(*fd_out);
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
	close(*fd_out);
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
		ssize_t bytes = read(0, buffer, sizeof(buffer) - 1);
		if (bytes < 0)
		{
			close(fds[0]);
			close(fds[1]);
			return -1;
		}
		buffer[bytes] = '\0';
		char *newline = ft_strchr(buffer, '\n');
		if (newline)
			*newline = '\0';
		if (ft_strcmp(buffer, word) == 0)
			break;
		if (write(fds[1], buffer, ft_strlen(buffer)) == -1 ||
			write(fds[1], "\n", 1) == -1)
		{
			perror("write error");
			close(fds[0]);
			close(fds[1]);
			return -1;
		}
	}
	close(fds[1]);
	if (dup2(fds[0], 0) == -1)
	{
		perror("dup2 error");
		close(fds[0]);
		return -1;
	}
	close(fds[0]);
	return 0;
}

void apply_redirections(t_env *cmds)
{
	int i = 0;
	int fd_in = -1;
	int fd_out = -1;

	while (cmds->arg[i])
	{
		if ((ft_strcmp(cmds->arg[i], "<") == 0 || ft_strcmp(cmds->arg[i], ">") == 0 ||
			ft_strcmp(cmds->arg[i], ">>") == 0 || ft_strcmp(cmds->arg[i], "<<") == 0) && cmds->arg[i + 1])
		{
			if (ft_strcmp(cmds->arg[i], "<") == 0 && handle_redir_input(cmds->arg[i + 1], &fd_in) == -1)
				perror("input redirection error");
			else if (ft_strcmp(cmds->arg[i], ">") == 0 && handle_redir_output(cmds->arg[i + 1], &fd_out) == -1)
				perror("output redirection error");
			else if (ft_strcmp(cmds->arg[i], ">>") == 0 && handle_redir_output_append(cmds->arg[i + 1], &fd_out) == -1)
				perror("append redirection error");
			else if (ft_strcmp(cmds->arg[i], "<<") == 0 && handle_redir_input_heredoc(cmds->arg[i + 1]) == -1)
				perror("heredoc error");
			cmds->arg[i] = NULL;
			cmds->arg[i + 1] = NULL;
		}
		i++;
	}
}
