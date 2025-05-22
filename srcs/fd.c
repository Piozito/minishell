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

#include "../lib/minishell.h"


int	handle_fd_input(char *file)
{
	if (ft_strchr(file, '<') || ft_strchr(file, '>'))
		return (-1);
	if (access(file, R_OK) == -1)
		return (-1);
	int fd_in = open(file, O_RDONLY);
	if (fd_in == -1)
		return (-1);
	if (dup2(fd_in, 0) == -1)
	{
		close(fd_in);
		return (-1);
	}
	close(fd_in);
	return (0);
}

int	handle_fd_output(char *file)
{
	if (ft_strchr(file, '<') || ft_strchr(file, '>'))
		return (-1);
	int fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
		return (-1);
	if (dup2(fd_out, 1) == -1)
	{
		close(fd_out);
		return (-1);
	}
	close(fd_out);
	return (0);
}

int	handle_fd_output_append(char *file)
{
	if (ft_strchr(file, '<') || ft_strchr(file, '>'))
		return (-1);
	int fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd_out == -1)
		return (-1);
	if (dup2(fd_out, 1) == -1)
	{
		close(fd_out);
		return (-1);
	}
	close(fd_out);
	return (0);
}
int	fd_checker(t_env *cmds, int i, int j)
{
	if (ft_strncmp(cmds->arg[i], ">>", 3) == 0)
		if (handle_fd_output_append(cmds->arg[i + 1]) == -1)
			j = 1;
	if (ft_strncmp(cmds->arg[i], "<", 2) == 0)
		if (handle_fd_input(cmds->arg[i + 1]) == -1)
			j = 2;
	if (ft_strncmp(cmds->arg[i], ">", 2) == 0)
		if (handle_fd_output(cmds->arg[i + 1]) == -1)
			j = 3;
	return (j);
}

int	apply_fd(t_env *cmds)
{
	int i = 0;
	int j = 0;
	apply_heredoc(cmds);
	while (cmds->arg[i])
	{
		j = 0;
		if ((ft_strncmp(cmds->arg[i], "<", 2) == 0 || ft_strncmp(cmds->arg[i],
					">", 2) == 0 || ft_strncmp(cmds->arg[i], ">>", 3) == 0
				|| ft_strncmp(cmds->arg[i], "<<", 3) == 0) && cmds->arg[i + 1])
		{
			j = fd_checker(cmds, i, j);
			if (j == 1)
				return (fd_error("append"));
			else if (j == 2)
				return (fd_error("input"));
			else if (j == 3)
				return (fd_error("output"));
			else
				remove_args(cmds->arg, i);
		}
		else
			i++;
	}
	return (0);
}
