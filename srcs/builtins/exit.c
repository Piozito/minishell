/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:56:36 by marvin            #+#    #+#             */
/*   Updated: 2025/05/26 13:50:54 by aaleixo-         ###   ########.fr       */
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
		exit(0);
	else if (cmds->arg[1] == NULL && is_numeric(cmds->arg[0]) == 1)
	{
		if (cmds->arg[0])
			exit(num_ex(cmds));
		exit(0);
	}
	else if (cmds->arg[0] && cmds->arg[1] == NULL)
	{
		write(cmds->fd, "non numeric arg \n", 18);
		exit(2);
	}
	else if (!cmds->arg[0])
		exit(0);
	else
	{
		write(cmds->fd, "too many arguments \n", 20);
		return (1);
	}
	return (128);
}
