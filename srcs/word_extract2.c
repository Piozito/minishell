/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_extract2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:11:18 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/02 16:13:31 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	extract_helper(char **result, size_t *allocated_size, size_t i)
{
	if (i >= *allocated_size - 1)
	{
		*result = ft_strrealloc(*result, allocated_size);
		if (!*result)
			return (1);
	}
	return (0);
}

void	quotes(const char *s, size_t idx, char *quote)
{
	if (!(*quote) && (s[idx] == '\'' || s[idx] == '\"'))
		*quote = s[idx];
	else if (*quote && s[idx] == *quote)
		*quote = 0;
}

int	extract_help(const char *s, size_t *index, char del, char *quote)
{
	if (del == '|')
	{
		handle_quote(s, index, (int *)quote);
	}
	return (0);
}

int	check_break(const char *s, size_t idx, char quote, char del)
{
	if (!quote && is_separator(s[idx], del, 0, 0))
		return (1);
	return (0);
}

void	duping(t_env *cmds)
{
	if (cmds->saved_stdin != -1)
	{
		dup2(cmds->saved_stdin, 0);
		close(cmds->saved_stdin);
		cmds->saved_stdin = -1;
	}
	if (cmds->saved_stdout != -1)
	{
		dup2(cmds->saved_stdout, 1);
		close(cmds->saved_stdout);
		cmds->saved_stdout = -1;
	}
}
