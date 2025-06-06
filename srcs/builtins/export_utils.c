/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:09:23 by fragarc2          #+#    #+#             */
/*   Updated: 2025/06/05 17:05:12 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

char	**bubble_sort(char **env, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (++i < n - 1)
	{
		j = -1;
		while (++j < n - i - 1)
		{
			if (ft_strncmp(env[j], env[j + 1], 1) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
		}
	}
	return (env);
}

void	export_print2(char **new_env, int i)
{
	write(1, "declare -x ", 11);
	if (is_chr(new_env[i], '=') == 0)
	{
		write(1, new_env[i], ft_strlen(new_env[i]));
		write(1, "\n", 1);
	}
	else
	{
		write(1, new_env[i], is_chr(new_env[i], '='));
		write(1, "\"", 1);
		ft_putstr_fd(new_env[i] + is_chr(new_env[i], '='), 1);
		write(1, "\"", 1);
		write(1, "\n", 1);
	}
}

void	export_print(t_env *env)
{
	int		i;
	int		j;
	char	**new_env;

	i = -1;
	j = 0;
	while (env->exp[j])
		j++;
	new_env = malloc(sizeof(char *) * (j + 1));
	if (!new_env)
		return ;
	while (++i < j)
		new_env[i] = env->exp[i];
	new_env[j] = NULL;
	new_env = bubble_sort(new_env, j);
	i = -1;
	while (new_env[++i])
		export_print2(new_env, i);
	free(new_env);
}

void	ex_refresh(t_env *env, int i)
{
	if (ft_strchr(env->arg[i], '='))
	{
		env->exp = update_env(ft_strdup(env->arg[i]), env->exp);
		env->env = update_env(ft_strdup(env->arg[i]), env->env);
	}
	else
		env->exp = update_env(ft_strdup(env->arg[i]), env->exp);
}

char	**new_env_maker(char **env, int j, char *arg)
{
	char	**new_env;

	new_env = malloc((j + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
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
