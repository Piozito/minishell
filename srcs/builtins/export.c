/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:36:59 by marvin            #+#    #+#             */
/*   Updated: 2025/05/14 10:20:19 by aaleixo-         ###   ########.fr       */
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

char **update_env(char *arg, char **env, int flag)
{
    int i = 0;
    int j = 0;
    char **new_env;

    while (env[i] && ft_strncmp(env[i], arg, is_chr(arg, '=')))
        i++;
    if (env[i])
    {
        if (is_chr(arg, '=') && flag == 1)
        {
            free(env[i]); // Free the old value before overwriting
            env[i] = ft_strdup(arg); // Always make a copy
        }
        return env;
    }
    new_env = (char **)malloc((i + 2) * sizeof(char *));
    if (!new_env)
        return NULL;
    while (j < i)
    {
        new_env[j] = env[j]; // Reuse existing pointers
        j++;
    }
    new_env[j] = ft_strdup(arg); // Always make a copy
    new_env[j + 1] = NULL;
    free(env); // Free the old array (not individual strings)
    return new_env;
}

int ft_export(t_env *env)
{
    int i;

    if (env->arg[0] == NULL)
    {
        i = 0;
        while (env->exp[i])
		{
			write(env->fd, "declare -x ", 11);
			write(env->fd, env->exp[i], ft_strlen(env->exp[i]));
			write (env->fd, "\n", 1);
			i++;
		}
        return (0);
    }
	if(env->arg[0][0] == '-')
	{
		write(env->fd, "export: export doens't accepts flags.\n", 39);
		return(2);
	}
    i = 0;
    while (env->arg[i])
    {
        if (is_valid(env->arg[i]))
        {
            if (ft_strchr(env->arg[i], '='))
			{
				env->exp = update_env(ft_strdup(env->arg[i]), env->exp, 1);
                env->env = update_env(ft_strdup(env->arg[i]), env->env, 1);
			}
            else
            {
                char *tmp = ft_strjoin(env->arg[i], "=");
                if (tmp)
                    env->exp = update_env(tmp, env->exp, 0);
            }
			i++;
        }
        else
		{
            write(env->fd, "export:: not a valid identifier\n", 33);
        	return (2);
		}
    }
	return(0);
}
