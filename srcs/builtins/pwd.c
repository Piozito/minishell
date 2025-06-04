/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:10:40 by fragarc2          #+#    #+#             */
/*   Updated: 2025/06/04 13:06:44 by aaleixo-         ###   ########.fr       */
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
