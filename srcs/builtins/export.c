/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:36:59 by marvin            #+#    #+#             */
/*   Updated: 2025/03/24 21:36:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static int is_chr(const char *str, int c)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i + 1);
        i++;
    }
    return (0);
}

static int is_valid(char *str)
{
    if (!str || (!ft_isalpha(*str) && *str != '_'))
        return (0);
    while (*str && *str != '=')
    {
        if (!ft_isalnum(*str) && *str != '_')
            return (0);
        str++;
    }
    return (1);
}

static void update_env(t_env *env, char *arg)
{
    int i;
    int j;
    char **new_env;
    i = 0;
    j = 0;
    while (env->env[i] && ft_strncmp(env->env[i], arg, is_chr(arg, '=')))
        i++;
    if (env->env[i])
    {
        if (is_chr(arg, '='))
        {
            free(env->env[i]);
            env->env[i] = arg;
        }
        else
            free(arg);
    }
    else
    {
        new_env = malloc((i + 2) * sizeof(char *));
        if (!new_env)
        {
            free(arg);
            return;
        }
        while (j < i)
        {
            new_env[j] = env->env[j];
            j++;
        }
        new_env[i] = arg;
        new_env[i + 1] = NULL;
        free(env->env);
        env->env = new_env;
    }
}

void ft_export(t_env *env, char **args)
{
    int i;

    if (!args[1])
    {
        i = 0;
        while (env->env[i])
            printf("%s\n", env->env[i++]);
        return;
    }
    i = 1;
    while (args[i])
    {
        if (is_valid(args[i]))
            update_env(env, ft_strdup(args[i]));
        i++;
    }
}

