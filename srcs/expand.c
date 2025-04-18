/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:22:32 by fragarc2          #+#    #+#             */
/*   Updated: 2025/04/15 15:09:06 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void replace_variable(char *result, char *str, char *start, char *end, char *expanded)
{
    int len_before = start - str;
    int len_expanded = ft_strlen(expanded);
    int len_after = ft_strlen(end);

    ft_strncpy(result, str, len_before);
    ft_strncpy(result + len_before, expanded, len_expanded);
    ft_strncpy(result + len_before + len_expanded, end, len_after);
    result[len_before + len_expanded + len_after] = '\0';
}

void ft_expand_variable(char *arg)
{
    char result[1024];
    char var_name[256];
    char *start;
    char *end;
    char *expanded;

    start = ft_strchr(arg, '$');
    if (!start)
        return;

    end = start + 1;
    while (*end && *end != ' ')
        end++;

    ft_strncpy(var_name, start + 1, end - (start + 1));
    var_name[end - (start + 1)] = '\0';

    expanded = getenv(var_name);
    if (!expanded)
        expanded = "";

    replace_variable(result, arg, start, end, expanded);
    ft_strncpy(arg, result, 1024 - 1);
}
