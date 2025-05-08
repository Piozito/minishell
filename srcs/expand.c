/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:22:32 by fragarc2          #+#    #+#             */
/*   Updated: 2025/05/08 11:11:12 by aaleixo-         ###   ########.fr       */
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

void ft_expand_variable(t_env *cmd, const char *src, int *index, char **dst, int *i)
{
    char var_name[256];
    char *start;
    char *end;
    char *expanded;
    int len_before;
    int len_expanded;
    int new_size;

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
	if(var_name[0] == '?' && var_name[1] == '\0')
		expanded = ft_itoa(cmd->exit_status);
	else
    	expanded = getenv(var_name);
    if (!expanded)
		expanded = "";
    len_expanded = ft_strlen(expanded);
    len_before = *i;
    new_size = len_before + len_expanded + 1;
    char *new_dst = (char *)malloc(new_size * sizeof(char));
    if (!new_dst)
    {
        write(1, "Memory allocation failed\n", 26);
        exit(127);
    }
    if (*dst)
    {
        ft_strlcpy(new_dst, *dst, len_before + 1);
        free(*dst);
    }
    ft_strlcpy(new_dst + len_before, expanded, len_expanded + 1);
    *dst = new_dst;
    *i += len_expanded;
}