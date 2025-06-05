/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:31:57 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/05 15:08:34 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	word_count_helper(const char *s, size_t *i, int *quote, char c)
{
	if (s[*i] == '\'' && !(quote[1]))
	{
		if (quote[0])
			quote[0] = 0;
		else if (ft_find_closing_quote(s, *i + 1, '\''))
			quote[0] = 1;
		(*i)++;
		return (1);
	}
	if (s[*i] == '\"' && !(quote[0]))
	{
		if (quote[1])
			quote[1] = 0;
		else if (ft_find_closing_quote(s, *i + 1, '\"'))
			quote[1] = 1;
		(*i)++;
		return (1);
	}
	if (is_separator(s[*i], c, quote[0], quote[1]))
		return (2);
	return (0);
}

int	word_count_m(const char *s, char c)
{
	size_t	i;
	size_t	count;
	int		quote[2];
	int		h;

	i = 0;
	count = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (s[i])
	{
		h = word_count_helper(s, &i, quote, c);
		if (h == 1)
			continue ;
		else if (h == 2)
		{
			if (!is_separator(s[i + 1], c, quote[0], quote[1]))
				count++;
		}
		i++;
	}
	if (s[0] && !is_separator(s[0], c, 0, 0))
		count++;
	return (count);
}

char	*extract_word(const char *s, size_t *index, char del)
{
	char	*result;
	size_t	allocated_size;
	size_t	i;
	char	quote;

	allocated_size = 1024;
	quote = 0;
	i = 0;
	result = ft_calloc(allocated_size, 1);
	if (!result)
		return (NULL);
	while (s[*index])
	{
		if (check_break(s, *index, quote, del))
			break ;
		quotes(s, *index, &quote);
		if (del == '|' && !quote)
			handle_redir(s, index, result, &i);
		result[i++] = s[(*index)++];
		if (extract_helper(&result, &allocated_size, i))
			return (NULL);
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strrealloc(char *result, size_t *size_ptr)
{
	char	*new_result;
	size_t	new_size;

	new_size = (*size_ptr) * 2;
	new_result = ft_calloc(new_size, 1);
	if (!new_result)
	{
		free(result);
		return (NULL);
	}
	ft_strlcpy(new_result, result, *size_ptr);
	free(result);
	*size_ptr = new_size;
	return (new_result);
}
