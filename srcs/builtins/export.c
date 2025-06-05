/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:36:59 by marvin            #+#    #+#             */
/*   Updated: 2025/06/05 15:22:08 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	is_chr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

static int	is_valid_env(char *str)
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

static int	find_env_index(char *arg, char **env)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = is_chr(arg, '=');
	if (key_len != 0)
		key_len = key_len - 1;
	else
		key_len = ft_strlen(arg);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], arg, key_len))
		{
			if (env[i][key_len] == '=' || env[i][key_len] == '\0')
				break ;
		}
		i++;
	}
	return (i);
}

char	**update_env(char *arg, char **env)
{
	int		i;
	int		j;
	char	**new_env;

	i = find_env_index(arg, env);
	j = 0;
	if (env && env[i])
	{
		if (is_chr(arg, '='))
		{
			free(env[i]);
			env[i] = arg;
		}
		else
			free(arg);
		return (env);
	}
	while (env && env[j])
		j++;
	new_env = new_env_maker(env, j, arg);
	free(env);
	return (new_env);
}

int	ft_export(t_env *env)
{
	int	i;

	if (env->arg[0] == NULL)
	{
		export_print(env);
		return (0);
	}
	if (env->arg[0][0] == '-')
	{
		write(1, "export: export doens't accepts flags.\n", 39);
		return (2);
	}
	i = -1;
	while (env->arg[++i])
	{
		if (is_valid_env(env->arg[i]))
			ex_refresh(env, i);
		else
		{
			write(1, "export:: not a valid identifier\n", 33);
			return (2);
		}
	}
	return (0);
}
