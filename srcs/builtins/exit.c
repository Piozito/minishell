/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:56:36 by marvin            #+#    #+#             */
/*   Updated: 2025/05/07 12:12:34 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_env *cmds)
{
	int	exit_status;


	if (cmds->flag[0] == NULL && cmds->arg[1] == NULL && !is_numeric(cmds->arg[0]))
	{
		if (cmds->arg[0])
		{
			exit_status = ft_atoi(cmds->arg[0]);
			if(exit_status > 255 || exit_status < 0)
			{
				write(cmds->fd, "exit: Error codes must be less than 256.\n", 42);
				return (255);
			}
			exit(exit_status % 256);
		}
		exit(0);
	}
	else
	{
		write(cmds->fd, "exit: exit only accepts a positive integer less than 256 and no flags.\n", 72);
		return (128);
	}
}
