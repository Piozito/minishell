/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:56:36 by marvin            #+#    #+#             */
/*   Updated: 2025/05/14 09:51:36 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;
	int num;

	i = 0;
	num = ft_atoi(str);
	while (str[i])
	{
		if (!ft_isdigit(num))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_env *cmds)
{
	int	exit_status;

	if(cmds->arg[0] == NULL)
		exit(0);
	if (!is_numeric(cmds->arg[0]))
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
