/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:36:46 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/04 12:54:15 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	heredoctor(char *word, int *fds, t_env *cmds)
{
	char	*expanded_line;
	char	*line;

	while (1)
	{
		expanded_line = NULL;
		line = readline("> ");
		if (!line || ft_strcmp(line, word) == 0)
		{
			free(line);
			return ;
		}
		expanded_line = hc_expand(cmds, line);
		if (!expanded_line)
			expanded_line = ft_strdup(line);
		write(fds[1], expanded_line, ft_strlen(expanded_line));
		write(fds[1], "\n", 1);
		free(line);
		free(expanded_line);
	}
}

int	handle_fd_input_heredoc(t_env *cmds, char *word)
{
	int	fds[2];

	if (cmds->heredoc != -1)
	{
		close(cmds->heredoc);
		cmds->heredoc = -1;
	}
	if (pipe(fds) == -1)
		return (-1);
	heredoctor(word, fds, cmds);
	close(fds[1]);
	cmds->heredoc = fds[0];
	return (0);
}

int	check_heredoc(t_env *cmds)
{
	char	*word;
	int		i;

	i = 0;
	if (!cmds->arg)
		return (1);
	while (cmds->arg[i])
	{
		if (ft_strncmp(cmds->arg[i], "<<", 3) == 0 && cmds->arg[i + 1])
		{
			word = get_file(cmds, i);
			if (!word || is_valid(word))
				return (fd_error("heredoc"));
			if (ft_strchr(word, '<') || ft_strchr(word, '>'))
				return (fd_error("heredoc"));
			if (handle_fd_input_heredoc(cmds, word) == -1)
				return (fd_error("heredoc"));
		}
		i++;
	}
	return (0);
}

int	apply_heredoc(t_env *cmds)
{
	if (cmds->heredoc != -1)
	{
		if (dup2(cmds->heredoc, 0) == -1)
		{
			close(cmds->heredoc);
			cmds->heredoc = -1;
			return (-1);
		}
		close(cmds->heredoc);
		cmds->heredoc = -1;
	}
	return (0);
}
