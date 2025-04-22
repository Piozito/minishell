/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:10:40 by fragarc2          #+#    #+#             */
/*   Updated: 2025/04/22 16:04:30 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	ft_pwd(t_env *cmds)
{
	char	cwd[1024];
	if (cmds->arg[0] != NULL || cmds->flag[0] != NULL)
	{
		write(cmds->fd, "pwd: pwd doesn't accept flags or arguments.\n", 45);
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) == 0)
		perror("pwd");
	write(cmds->fd, cwd, ft_strlen(cwd));
	write(cmds->fd, "\n", 1);
	return ;
}
