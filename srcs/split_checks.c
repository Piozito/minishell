/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:41:33 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/27 13:42:24 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	handle_quote(const char *s, size_t *index, int *quote_flag)
{
	if ((*quote_flag == 0) && (s[*index] == '\'' || s[*index] == '\"'))
	{
		if (ft_find_closing_quote(s, *index + 1, s[*index]))
			*quote_flag = s[*index];
		return (0);
	}
	if (*quote_flag && s[*index] == *quote_flag)
		*quote_flag = 0;
	return (0);
}

int	handle_redir(const char *s, size_t *index, char *result, size_t *i)
{
	if (s[*index] == '<' || s[*index] == '>')
	{
		result[(*i)++] = ' ';
		result[(*i)++] = s[(*index)++];
		if (s[*index] == '<' || s[*index] == '>')
			result[(*i)++] = s[(*index)++];
		result[(*i)++] = ' ';
		return (1);
	}
	return (0);
}

static char	*strip_closed_quotes(const char *src)
{
	int		j;
	int		k;
	int		quote;
	char	*new;

	j = 0;
	k = 0;
	quote = 0;
	new = malloc(ft_strlen(src) + 1);
	if (!new)
		return (NULL);
	while (src[j])
	{
		if (!quote && (src[j] == '\'' || src[j] == '\"')
			&& ft_find_closing_quote(src, j + 1, src[j]))
			quote = src[j];
		else if (quote && src[j] == quote)
			quote = 0;
		else
			new[k++] = src[j];
		j++;
	}
	new[k] = '\0';
	return (new);
}

void	remove_closed_quotes(char **result)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!result)
		return ;
	while (result[i])
	{
		if (!result[i])
		{
			i++;
			continue ;
		}
		tmp = strip_closed_quotes(result[i]);
		if (tmp)
		{
			free(result[i]);
			result[i] = tmp;
		}
		i++;
	}
}

int	check_redirs(char **result)
{
	int	i;

	i = 0;
	if (!result)
		return (0);
	while (result[i])
	{
		if (result[i][0] && (result[i][0] == '<' || result[i][0] == '>'))
		{
			if ((result[i][1] == '<' || result[i][1] == '>') &&
				(result[i][2] == '<' || result[i][2] == '>'))
				return (1);
			if (result[i][1] && (result[i][1] == '<' || result[i][1] == '>') &&
				result[i][0] != result[i][1])
				return (1);
			if ((!result[i][1] && !result[i + 1]) ||
				(result[i][1] && (result[i][1] == '<' || result[i][1] == '>') &&
				!result[i][2] && !result[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}
