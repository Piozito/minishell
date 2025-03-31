/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:10:40 by fragarc2          #+#    #+#             */
/*   Updated: 2025/03/31 15:46:14 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	ft_pwd(void)
{
	char	cwd[MAX_PATH];

	if (getcwd(cwd, sizeof(cwd)) == 0)
		perror("pwd");
	printf("%s\n", cwd);
	return (0);
}
