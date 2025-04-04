/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:36:59 by marvin            #+#    #+#             */
/*   Updated: 2025/04/04 09:07:09 by aaleixo-         ###   ########.fr       */
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
    int i = 0;
    int j = 0;
    char **new_env;
    
    while (env->env[i] && ft_strncmp(env->env[i], arg, is_chr(arg, '=')))
        i++;
    
    if (env->env[i])
    {
        if (is_chr(arg, '='))
            env->env[i] = arg;
        else
            free(arg);
    }
    else
    {
        new_env = malloc((i + 2) * sizeof(char *));
        if (!new_env)
            return;
        while (env->env[j])
        {
            new_env[j] = env->env[j];
            j++;
        }
        new_env[j] = arg;
        new_env[j + 1] = NULL;
        env->env = new_env;
    }
}

void ft_export(t_env *env)
{
    int i;

	if(env->flag[0] != NULL)
	{
		printf("export: export doens't accepts flags.\n");
		return ;
	}
    if (!env->arg[0])
    {
        i = 0;
        while (env->env[i])
            printf("declare -x %s\n", env->env[i++]);
        return;
    }
    i = 0;
    while (env->arg[i])
    {
        if (is_valid(env->arg[i]))
        {
            char *eq = ft_strchr(env->arg[i], '=');
            if (eq)
                update_env(env, ft_strdup(env->arg[i]));
            else
            {
                char *tmp = ft_strjoin(env->arg[i], "=");
                if (tmp)
                    update_env(env, tmp);
            }
        }
        else
            printf("export: `%s': not a valid identifier\n", env->arg[i]);
        i++;
    }
}
