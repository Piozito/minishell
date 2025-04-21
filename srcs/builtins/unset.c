/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:19:52 by marvin            #+#    #+#             */
/*   Updated: 2025/04/21 16:29:03 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void	remove_env_var(t_env *env, const char *var)
{
	int	i;

	if (!env || !var)
		return ;
	i = 0;
	while (env->env[i])
	{
		if (ft_strncmp(env->env[i], var, ft_strlen(var)) == 0
			&& env->env[i][ft_strlen(var)] == '=')
		{
			while (env->env[i])
			{
				env->env[i] = env->env[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}

void	ft_unset(t_env *cmds, int fd)
{
	int	i;

	i = 0;
	if(cmds->flag[0] != NULL)
	{
		write(fd, "unset: unset doesn't accept flags.\n", 36);
		return ;
	}
	while (cmds->arg[i])
	{
		if (ft_strcmp(cmds->arg[i], "_") != 0)
			remove_env_var(cmds, cmds->arg[i]);
		i++;
	}
}
