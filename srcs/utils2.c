/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:39:06 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/21 12:03:16 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static int	is_separator(char ch, char c, int quote, int dquote)
{
	if (c == ' ')
		return (!quote && !dquote && (ch == c || ch == '\t' || ch == '\0'));
	return (!quote && !dquote && (ch == c || ch == '\0'));
}

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

char *ft_strrealloc(char *result, size_t *size_ptr)
{
    char *new_result;
    size_t new_size = (*size_ptr) * 2;

    new_result = (char *)malloc(new_size * sizeof(char));
    if (!new_result)
    {
        free(result);
        return (NULL);
    }
    ft_strlcpy(new_result, result, *size_ptr);
    free(result);
    *size_ptr = new_size;
    return new_result;
}

static int	word_count(const char *s, char c)
{
	size_t	i;
	size_t	count;
	int	quote;
	int	dquote;

	i = 0;
	count = 0;
	quote = 0;
	dquote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !dquote)
		{
			if (quote)
				quote = 0;
			else if (ft_find_closing_quote(s, i + 1, '\''))
				quote = 1;
			i++;
			continue ;
		}
		else if (s[i] == '\"' && !quote)
		{
			if (dquote)
				dquote = 0;
			else if (ft_find_closing_quote(s, i + 1, '\"'))
				dquote = 1;
			i++;
			continue ;
		}
		else if (is_separator(s[i], c, quote, dquote))
		{
			if (!is_separator(s[i + 1], c, quote, dquote))
				count++;
		}
		i++;
	}
	if (s[0] && !is_separator(s[0], c, 0, 0))
		count++;
	return (count);
}

char	**pipe_check(t_env *cmds, const char *input)
{
	size_t	i;
	int	pipe;

	i = 0;
	pipe = 0;
	if (input[0] == '|')
	{
		printf("pipe: parsing error.\n");
		return (NULL);
	}
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (input[i] == '\'')
			{
				if (ft_find_closing_quote(input, i + 1, '\''))
				{
					pipe = 0;
					i++;
					while (input[i] != '\'')
						i++;
				}
			}
			else if (input[i] == '\"')
			{
				if (ft_find_closing_quote(input, i + 1, '\"'))
				{
					pipe = 0;
					i++;
					while (input[i] != '\"')
						i++;
				}
			}
		}
		else if (input[i] == '|')
		{
			if (pipe == 1)
			{
				printf("pipe: parsing error.\n");
				return (NULL);
			}
			else
				pipe = 1;
		}
		else if (input[i] != ' ' && input[i] != '|' && input[i] != '\t' && input[i] != '\0')
			pipe = 0;
		i++;
	}
	if (pipe == 1)
	{
		printf("pipe: parsing error.\n");
		return (NULL);
	}
	return (ft_split_quotes(cmds, input, '|', 0));
}

static char	*extract_word(t_env *cmd, const char *s, size_t *index, char delimiter, int del)
{
	char	*result;
	size_t		i;
	int		quote;
	int		dquote;
	size_t		size;

	i = 0;
	quote = 0;
	dquote = 0;
	size = 1024;
	result = (char *)malloc(size * sizeof(char));
	if (!result)
		return (NULL);
	while (s[*index] && !is_separator(s[*index], delimiter, quote, dquote))
	{
		if(!quote && !dquote && (s[*index] == '<' || s[*index] == '>') && delimiter != 27)
		{
			if(delimiter == '|')
			{
				check_heredoc(cmd, s, index);
				if(s[*index] == '<' || s[*index] == '>')
				{
					result[i++] = ' ';
					result[i++] = s[(*index)++];
					if(s[*index] == '<' || s[*index] == '>')
						result[i++] = s[(*index)++];
					if(s[*index] == '<' || s[*index] == '>')
					{
						write(2, "redirectiong parsing error.\n", 28);
						return NULL;
					}
					result[i++] = ' ';
				}
			}
		}
		if (s[*index] == '\'' && !dquote && delimiter != 27)
		{
			if (!quote && s[*index + 1] == '\'' && s[*index + 2] != '\0')
				(*index) += 2;
			else if (quote)
			{
				quote = 0;
				if (del == 0)
					result[i++] = s[(*index)++];
				else if (del == 1)
					(*index)++;
			}
			else if (ft_find_closing_quote(s, *index + 1, '\''))
			{
				quote = 1;
				if (del == 0)
					result[i++] = s[(*index)++];
				else if (del == 1)
					(*index)++;
			}
			result[i++] = s[(*index)++];
		}
		else if (s[*index] == '\"' && !quote && delimiter != 27)
		{
			if (!dquote && s[*index + 1] == '\"' && s[*index + 2] != '\0')
				(*index) += 2;
			else if (dquote)
			{
				dquote = 0;
				if (del == 0)
					result[i++] = s[(*index)++];
				else if (del == 1)
					(*index)++;
			}
			else if (ft_find_closing_quote(s, *index + 1, '\"'))
			{
				dquote = 1;
				if (del == 0)
					result[i++] = s[(*index)++];
				else if (del == 1)
					(*index)++;
			}
			result[i++] = s[(*index)++];
		}
		else
			result[i++] = s[(*index)++];
		if (i >= size - 1)
			result = ft_strrealloc(result, &size);
	}
	result[i] = '\0';
	return (result);
}

char **ft_split_quotes(t_env *cmd, const char *s, char delimiter, int del)
{
    char **result;
    size_t i;
    size_t index;
    size_t words;

    i = 0;
    index = 0;
    words = word_count(s, delimiter);
    if (!s)
        return (NULL);
    result = (char **)malloc((words + 1) * sizeof(char *));
    if (!result)
        return (NULL);
    while (i < words)
    {
        while (s[index] && is_separator(s[index], delimiter, 0, 0))
            index++;
        if (s[index] && !is_separator(s[index], delimiter, 0, 0))
        {
            result[i] = extract_word(cmd, s, &index, delimiter, del);
            if(!result[i])
                return NULL;
        }
        i++;
    }
    result[i] = NULL;
    expand_variables(cmd, result);
    return (result);
}