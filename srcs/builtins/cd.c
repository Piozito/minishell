/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:46:18 by fragarc2          #+#    #+#             */
/*   Updated: 2025/06/09 15:29:03 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static char	*homer(t_env *cmds)
{
	char	*home;

	home = env_expander(cmds, "HOME=");
	if (home[0] == '\0')
	{
		free(home);
		ft_putstr_fd("HOME is not set.\n", 2);
		return (NULL);
	}
	return (home);
}

static char	*get_cd_path(t_env *cmds, char *path)
{
	char	*old_pwd;

	if (!path || !*path)
		return (homer(cmds));
	if (ft_strcmp(path, "-") == 0)
	{
		old_pwd = env_expander(cmds, "OLDPWD=");
		if (old_pwd[0] == '\0')
		{
			free(old_pwd);
			ft_putstr_fd("OLDPWD is not set.\n", 2);
			return (NULL);
		}
		return (old_pwd);
	}
	return (ft_strdup(path));
}

static void	update_pwd(t_env *cmds, char *old_pwd)
{
	char	*new_pwd;
	char	*tmp;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		tmp = ft_strjoin("OLDPWD=", old_pwd);
		ft_putenv(cmds, tmp);
		free(tmp);
		tmp = ft_strjoin("PWD=", new_pwd);
		ft_putenv(cmds, tmp);
		free(tmp);
		free(new_pwd);
	}
	else
		perror("getcwd");
}

int	cd_error(char *path, char *old_pwd)
{
	write(1, "cd: no such file or directory: ", 32);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(old_pwd);
	free(path);
	return (1);
}

int	ft_cd(t_env *cmds)
{
	char	*old_pwd;
	char	*path;

	old_pwd = getcwd(NULL, 0);
	if ((cmds->arg[0] == NULL || cmds->arg[1] == NULL))
	{
		path = get_cd_path(cmds, cmds->arg[0]);
		if (!path)
			return (1);
		if (chdir(path) != 0 && ft_strcmp(path, "-") != 0)
			return (cd_error(path, old_pwd));
		if (old_pwd)
			update_pwd(cmds, old_pwd);
	}
	else
	{
		write(1, "cd: cant accept flags or more than 1 arg.\n", 54);
		return (2);
	}
	free(old_pwd);
	free(path);
	return (0);
}
