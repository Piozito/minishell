/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:37:23 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/05 15:19:21 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*ft_find_closing_quote(const char *str, int start, char quote)
{
	int	i;

	i = start;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}

void	pipe_quote_check(const char *input, size_t *i, int *pipe, char *quote)
{
	if ((input[*i] == '\'' || input[*i] == '\"'))
	{
		if (*quote == 0)
		{
			if (ft_find_closing_quote(input, *i + 1, input[*i]))
			{
				*quote = input[*i];
				(*i)++;
				while (input[*i] && input[*i] != *quote)
					(*i)++;
				if (input[*i] == *quote)
					*quote = 0;
			}
		}
		else if (*quote == input[*i])
			*quote = 0;
		*pipe = 0;
	}
	else if (input[*i] != ' ' && input[*i] != '|'
		&& input[*i] != '\t' && input[*i] != '\0' && *quote == 0)
		*pipe = 0;
}

char	**pipe_check(t_env *cmds, const char *input)
{
	size_t	i;
	int		pipe;
	char	quote;

	i = 0;
	pipe = 1;
	quote = 0;
	while (input[i] != '\0')
	{
		pipe_quote_check(input, &i, &pipe, &quote);
		if ((input[i] == '|' || input[0] == '|') && !quote)
		{
			if (pipe != 0)
				break ;
			else
				pipe = 1;
		}
		i++;
	}
	if (pipe == 1)
		if (general_error("Parsing pipe error.", 1, 0, cmds))
			return (NULL);
	return (ft_split_quotes(cmds, input, '|'));
}

void	ft_split_quotes_helper(char **res, const char *s, char del, size_t w)
{
	size_t	i;
	size_t	index;

	i = 0;
	index = 0;
	while (i < w)
	{
		while (s[index] && is_separator(s[index], del, 0, 0))
			index++;
		if (s[index] && !is_separator(s[index], del, 0, 0))
		{
			res[i] = extract_word(s, &index, del);
			if (!res[i])
				res[i] = ft_strdup("");
		}
		i++;
	}
	res[i] = NULL;
}

char	**ft_split_quotes(t_env *cmd, const char *s, char delimiter)
{
	char	**result;
	size_t	words;

	if (!s)
		return (NULL);
	words = word_count_m(s, delimiter);
	result = (char **)ft_calloc((words + 1) * sizeof(char *), 1);
	if (!result)
		return (NULL);
	ft_split_quotes_helper(result, s, delimiter, words);
	if (delimiter == ' ')
	{
		expand_variables(cmd, result);
		remove_closed_quotes(result);
	}
	if (check_redirs(result))
	{
		general_error("Redirection parsing error.", 1, 0, cmd);
		return (NULL);
	}
	return (result);
}
