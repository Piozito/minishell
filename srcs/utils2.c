/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funky_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:39:06 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/04 19:30:15 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int is_separator(char ch, char c)
{
    return ch == c || ch == '\0';
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
        else if (!quote && !dquote && is_separator(s[i], c) && !is_separator(s[i + 1], c))
            count++;
        i++;
    }
    if (!is_separator(s[0], c))
        count++;
    return count;
}

static int word_length(char const *s, char c)
{
    int i = 0;
    int len = 0;
    int quote = 0;
    int dquote = 0;

    while (s[i] != '\0' && (!is_separator(s[i], c) || quote || dquote))
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

static char **f(char const *s, char c, char **result, int words_count)
{
    int i;
    int j;
    int w_len;

    while (*s == c)
        s++;
    i = -1;
    while (++i < words_count)
    {
        while (*s == c)
            s++;
        j = 0;
        w_len = word_length(s, c);
        result[i] = (char *)malloc(sizeof(char) * (w_len + 1));
        if (!(result[i]))
        {
            while (i > 0)
                free(result[--i]);
            free(result);
            return (NULL);
        }
        while (j < w_len)
        {
            if (*s == '\'' || *s == '\"')
            {
                char quote_char = *s;
                result[i][j++] = *s++;
                while (*s && *s != quote_char)
                    result[i][j++] = *s++;
                if (*s)
                    result[i][j++] = *s++;
            }
            else
                result[i][j++] = *s++;
        }
        result[i][j] = '\0';
    }
    return (result);
}

char **ft_split_quotes(char const *s, char c)
{
    char **result;
    int wcount;

    if (!s)
        return (NULL);
    wcount = word_count(s, c);
    result = (char **)malloc(sizeof(char *) * (wcount + 1));
    if (!(result))
        return (NULL);
    result = f(s, c, result, wcount);
    result[wcount] = NULL;
    return (result);
}