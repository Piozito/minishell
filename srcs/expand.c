/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:22:32 by fragarc2          #+#    #+#             */
/*   Updated: 2025/04/10 13:51:51 by fragarc2         ###   ########.fr       */
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
    char result[MAX_PATH];
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
    ft_strncpy(arg, result, MAX_PATH - 1);
}
