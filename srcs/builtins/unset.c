/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:19:52 by marvin            #+#    #+#             */
/*   Updated: 2025/04/04 18:54:16 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void	remove_env_var(t_env *env, const char *var)
{
	int	i;
	extern char **environ;

	if (!env || !environ || !var)
		return ;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var, ft_strlen(var)) == 0
			&& environ[i][ft_strlen(var)] == '=')
		{
			while (environ[i])
			{
				environ[i] = environ[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}

void	ft_unset(t_env *cmds)
{
	int	i;

	i = 0;
	if(cmds->flag[0] != NULL)
	{
		printf("unset: unset doesn't accept flags.\n");
		return ;
	}
	while (cmds->arg[i])
	{
		if (ft_strcmp(cmds->arg[i], "_") != 0)
			remove_env_var(cmds, cmds->arg[i]);
		i++;
	}
}
