/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:36:59 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 16:09:50 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

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
    while (env->env[i] && ft_strncmp(env->env[i], arg, ft_strlen(arg)))
        i++;
    if (env->env[i])
    {
        free(env->env[i]);
        env->env[i] = ft_strdup(arg);
    }
    else
    {
        new_env = malloc((i + 2) * sizeof(char *));
        if (!new_env)
            return;
        while (++j < i)
            new_env[j] = env->env[j];
        new_env[i] = ft_strdup(arg);
        new_env[i + 1] = NULL;
        free(env->env);
        env->env = new_env;
    }
    free(arg);
}

void ft_export(t_env *env)
{
    int i;

    if (!env->arg[1])
    {
        i = 0;
        while (env->env[i])
            printf("%s\n", env->env[i++]);
        return;
    }
    i = 1;
    while (env->arg[i])
    {
        if (is_valid(env->arg[i]))
            update_env(env, env->arg[i]);
        i++;
    }
}