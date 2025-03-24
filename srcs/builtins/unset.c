/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:19:52 by marvin            #+#    #+#             */
/*   Updated: 2025/03/24 12:17:51 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void remove_env_var(t_env *env, const char *var)
{
    int i;
    int j;

    i = 0;
    while (env->env[i])
    {
        if (ft_strncmp(env->env[i], var, ft_strlen(var)) == 0
            && env->env[i][ft_strlen(var)] == '=')
        {
            free(env->env[i]);
            j = i;
            while (env->env[j])
            {
                env->env[j] = env->env[j + 1];
                j++;
            }
            return ;
        }
        i++;
    }
}

void ft_unset(t_env *env, char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        if (ft_strcmp(args[i], "_") != 0)
            remove_env_var(env, args[i]);
        i++;
    }
}