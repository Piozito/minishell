/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:22:32 by fragarc2          #+#    #+#             */
/*   Updated: 2025/04/30 10:20:44 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void replace_variable(char *result, const char *str, char *start, char *end, char *expanded)
{
    int len_before = start - str;
    int len_expanded = ft_strlen(expanded);
    int len_after = ft_strlen(end);

    ft_strlcpy(result, str, len_before + 1);
    ft_strlcpy(result + len_before, expanded, len_expanded + 1);
    ft_strlcpy(result + len_before + len_expanded, end, len_after + 1);
    result[len_before + len_expanded + len_after] = '\0';
}

void ft_expand_variable(const char *src, int *index, char **dst, int *i)
{
    char result[1024];
    char var_name[256];
    char *start;
    char *end;
    char *expanded;

    if (src[*index] != '$')
        return;
    start = (char *)src + *index;
    end = start + 1;
    while (*end && *end != ' ' && *end != '\"' && *end != '\'')
    {
        (*index)++;
        end++;
    }
    ft_strlcpy(var_name, start + 1, end - (start + 1) + 1);
    var_name[end - (start + 1)] = '\0';
    expanded = getenv(var_name);
    if (!expanded)
        expanded = "";
    *i += strlen(expanded);
    replace_variable(result, src, start, end, expanded);
    char *new_dst = (char *)malloc(strlen(result) + 1);
    if (!new_dst)
    {
        write(1, "Memory allocation failed\n", 27);
        exit(127);
    }
    ft_strlcpy(new_dst, result, ft_strlen(result) + 1);
    free(*dst);
    *dst = new_dst;
}