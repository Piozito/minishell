/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:39:06 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/10 13:02:43 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static int is_separator(char ch, char c, int quote, int dquote)
{
    return !quote && !dquote && (ch == c || ch == '\0');
}

static int word_count(char const *s, char c)
{
    int i = 0;
    int count = 0;
    int quote = 0;
    int dquote = 0;

    while (s[i])
    {
        if (s[i] == '\'' && !dquote)
            quote = !quote;
        else if (s[i] == '\"' && !quote)
            dquote = !dquote;
        else if (is_separator(s[i], c, quote, dquote) && !is_separator(s[i + 1], c, quote, dquote))
            count++;
        i++;
    }
    if (!is_separator(s[0], c, quote, dquote))
        count++;
    return count;
}

static int word_length(char const *s, char c)
{
    int i = 0;
    int len = 0;
    int quote = 0;
    int dquote = 0;

    while (s[i] != '\0' && !is_separator(s[i], c, quote, dquote))
    {
        if (s[i] == '\'' && !dquote)
            quote = !quote;
        else if (s[i] == '\"' && !quote)
            dquote = !dquote;
        len++;
        i++;
    }
    return len;
}

static char *ft_find_closing_quote(const char *str, int start, char quote)
{
    int i = start;
    while (str[i] != '\0')
    {
        if (str[i] == quote)
            return (char *)(str + i);
        i++;
    }
    return (NULL);
}

static char *extract_word(const char *s, int *index, char delimiter)
{
    char *result;
    int start = *index;
    int i = 0;
    int len = word_length(s + start, delimiter);
    int quote = 0;
    int dquote = 0;

    result = (char *)malloc((len + 1) * sizeof(char));
    if (!result)
        return (NULL);

    while (s[*index] && !is_separator(s[*index], delimiter, quote, dquote))
    {
        if (s[*index] == '\'' && !dquote)
        {
            if (quote)
            {
                quote = 0;
                (*index)++;
                continue;
            }
            if (ft_find_closing_quote(s, *index + 1, '\''))
            {
                quote = 1;
                (*index)++;
                continue;
            }
            result[i++] = s[(*index)++];
        }
        else if (s[*index] == '\"' && !quote)
        {
            if (dquote)
            {
                dquote = 0;
                (*index)++;
                continue;
            }
            if (ft_find_closing_quote(s, *index + 1, '\"'))
            {
                dquote = 1;
                (*index)++;
                continue;
            }
            result[i++] = s[(*index)++];
        }
        else
        {
            result[i++] = s[*index];
            (*index)++;
        }
    }
    result[i] = '\0';
    return result;
}

static char **split_string(const char *s, char delimiter)
{
    char **result;
    int i = 0;
    int index = 0;
    int words = word_count(s, delimiter);

    result = (char **)malloc((words + 1) * sizeof(char *));
    if (!result)
        return (NULL);
    while (i < words)
    {
        while (s[index] && is_separator(s[index], delimiter, 0, 0))
            index++;
        if (s[index] && !is_separator(s[index], delimiter, 0, 0))
            result[i++] = extract_word(s, &index, delimiter);
    }
    result[i] = NULL;
    return (result);
}

char **ft_split_quotes(const char *s, char delimiter)
{
    if (!s)
        return (NULL);
    return (split_string(s, delimiter));
}
