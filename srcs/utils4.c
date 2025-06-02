/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:39:09 by fragarc2          #+#    #+#             */
/*   Updated: 2025/06/02 16:02:32 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	if (*big == '\0')
		return (NULL);
	i = 0;
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

void	command_not_found(char *cmd)
{
	char	*full_str;
	char	*temp;

	temp = ft_strjoin("command not found: \"", cmd);
	full_str = ft_strjoin(temp, "\"\n");
	write(2, full_str, ft_strlen(full_str));
	free(temp);
	free(full_str);
}

int	executable_check(t_env *cmds)
{
	int	i;

	i = 0;
	if (!cmds->cmd && cmds->arg[0])
	{
		if (!cmds->arg[1])
			return (1);
		if (ft_strncmp(cmds->arg[0], ">", 1) == 0
			|| ft_strncmp(cmds->arg[1], "<", 1) == 0)
			apply_fd(cmds);
		return (1);
	}
	while (cmds->cmd[i])
	{
		if (ft_isalpha(cmds->cmd[i]) == 1)
			return (0);
		i++;
	}
	return (1);
}

char	*get_file(t_env *cmds, size_t i)
{
	size_t	j;

	j = 0;
	if (ft_strncmp(cmds->arg[i], "<<", 3) == 0)
		i++;
	else
		return (NULL);
	if (ft_strchr(cmds->arg[i], '<') || ft_strchr(cmds->arg[i], '>'))
		return (NULL);
	while (cmds->arg[i][j])
	{
		if (ft_isalnum(cmds->arg[i][j]) == 0)
			return (NULL);
		j++;
	}
	return (cmds->arg[i]);
}

int	env_tester(t_env *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->env[i])
	{
		j = 0;
		while (cmd->env[i][j])
		{
			if (j > 131071)
			{
				write(2, "env too long \n", 15);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
