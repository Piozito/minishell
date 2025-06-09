/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:56:36 by marvin            #+#    #+#             */
/*   Updated: 2025/06/09 18:58:38 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	num_ex(t_env *cmds)
{
	int	exit_status;

	exit_status = ft_atoi(cmds->arg[0]);
	return (exit_status % 256);
}

int	ft_exit(t_env *cmds)
{
	if (!cmds->arg[0])
		exit(ft_clear(cmds));
	else if (cmds->arg[1] == NULL && is_numeric(cmds->arg[0]) == 1)
	{
		if (cmds->arg[0])
			cmds->exit_status = num_ex(cmds);
		exit(ft_clear(cmds));
	}
	else if (cmds->arg[0] && cmds->arg[1] == NULL)
	{
		write(1, "non numeric arg \n", 18);
		ft_clear(cmds);
		exit(2);
	}
	else if (!cmds->arg[0])
		exit(ft_clear(cmds));
	else
	{
		write(1, "exit \n", 7);
		write(1, "too many arguments \n", 20);
		return (1);
	}
	return (128);
}
