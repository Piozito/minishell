/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:10:40 by fragarc2          #+#    #+#             */
/*   Updated: 2025/06/02 17:38:59 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	ft_pwd(t_env *cmds)
{
	char	*cwd;

	if (cmds->arg[0] && cmds->arg[0][0] == '-')
	{
		write(cmds->fd, "pwd: pwd doesn't accept flags or arguments.\n", 45);
		return (2);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("pwd");
	write(cmds->fd, cwd, ft_strlen(cwd));
	write(cmds->fd, "\n", 1);
	return (0);
}
