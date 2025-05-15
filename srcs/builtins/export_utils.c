/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:09:23 by fragarc2          #+#    #+#             */
/*   Updated: 2025/05/15 16:42:46 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void bubble_sort(char **env, int n)
{
	int i;
	int j;
	char *tmp;
	i = -1;
	while (++i < n - 1)
	{
		j = -1;
		while (++j < n - i - 1)
		{
			if (strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
		}
	}
}

void export_print2(t_env *env, char **new_env, int i)
{
		write(env->fd, "declare -x ", 11);
		if (is_chr(new_env[i], '=') == 0)
		{
			write(env->fd, new_env[i], strlen(new_env[i]));
			write(env->fd, "\n", 1);
		}
		else
		{
			write(env->fd, new_env[i], is_chr(new_env[i], '='));
			write(env->fd, "\"", 1);
			ft_putstr_fd(new_env[i] + is_chr(new_env[i], '='), env->fd);
			write(env->fd, "\"", 1);
			write(env->fd, "\n", 1);
		}

}

void export_print(t_env *env)
{
	int i = -1;
	int j = 0;

	while (env->exp[j])
		j++;
	char **new_env = malloc(sizeof(char *) * (j + 1));
	if (!new_env)
		return;
	while (++i < j)
		new_env[i] = env->exp[i];
	new_env[j] = NULL;
	bubble_sort(new_env, j);
	i = -1;
	while (new_env[++i])
	{
		export_print2(env, new_env, i);
	}
	free(new_env);
}

void ex_refresh(t_env *env, int i)
{
	if (ft_strchr(env->arg[i], '='))
	{
		env->exp = update_env(ft_strdup(env->arg[i]), env->exp);
		env->env = update_env(ft_strdup(env->arg[i]), env->env);
	}
	else
			env->exp = update_env(ft_strdup(env->arg[i]), env->exp);
}

char **new_env_maker(char **env, int j, char *arg)
{
	char **new_env;

	new_env = malloc((j + 2) * sizeof(char *));
    if (!new_env)
        return NULL;
    j = 0;
    while (env && env[j])
    {
        new_env[j] = env[j];
        j++;
    }
    new_env[j] = arg;
    new_env[j + 1] = NULL;
	return (new_env);
}
