/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:36:59 by marvin            #+#    #+#             */
/*   Updated: 2025/05/07 12:20:03 by fragarc2         ###   ########.fr       */
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

char **update_env(char *arg, char **env)
{
    int i = 0;
    int j = 0;
    char **new_env;

    while (env[i] && ft_strncmp(env[i], arg, is_chr(arg, '=')))
    	i++;
    if (env[i])
    {
        if (is_chr(arg, '='))
            env[i] = arg;
        else
            free(arg);
	}
    else
    {
        new_env = malloc((i + 2) * sizeof(char *));
        if (!new_env)
            return(0);
        while (env[j])
        {
            new_env[j] = env[j];
            j++;
        }
        new_env[j] = arg;
        new_env[j + 1] = NULL;
        env = new_env;
    }
	return (env);
}

int ft_export(t_env *env)
{
    int i;

	if(env->flag[0] != NULL)
	{
		write(env->fd, "export: export doens't accepts flags.\n", 39);
		return(2);
	}
    if (!env->arg[0])
    {
        i = 0;
        while (env->exp[i])
		{
			write(env->fd, "declare -x", 11);
			write(env->fd, env->exp[i], ft_strlen(env->exp[i]));
			write (env->fd, "\n", 1);
			i++;
		}
        return (0);
    }
    i = 0;
    while (env->arg[i])
    {
        if (is_valid(env->arg[i]))
        {
            if (ft_strchr(env->arg[i], '='))
			{
                env->env = update_env(ft_strdup(env->arg[i]), env->env);
				env->exp = update_env(ft_strdup(env->arg[i]), env->exp);
			}
            else
            {
                char *tmp = ft_strjoin(env->arg[i], "=");
                if (tmp)
                    env->exp = update_env(tmp, env->exp);
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
