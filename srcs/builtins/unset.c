/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:19:52 by marvin            #+#    #+#             */
/*   Updated: 2025/06/04 13:26:22 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void	remove_env_var(char **env, const char *var)
{
	int	i;

	if (!env || !var)
		return ;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0
			&& env[i][ft_strlen(var)] == '=')
		{
			while (env[i])
			{
				env[i] = env[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}

int	ft_unset(t_env *cmds)
{
	int	i;

	i = 0;
	if (cmds->arg[0][0] == '-')
	{
		write(cmds->fd, "unset: unset doesn't accept flags.\n", 36);
		return (2);
	}
	while (cmds->arg[i])
	{
		if (ft_strcmp(cmds->arg[i], "_") != 0)
		{
			remove_env_var(cmds->exp, cmds->arg[i]);
			remove_env_var(cmds->env, cmds->arg[i]);
		}
		i++;
	}
	return (0);
}
