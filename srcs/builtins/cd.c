/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:46:18 by fragarc2          #+#    #+#             */
/*   Updated: 2025/05/26 15:04:14 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void	ft_putenv(t_env *cmds, char *var)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(var);
	while (cmds->env[i])
	{
		if (ft_strncmp(var, "OLDPWD=", 7) == 0
			&& ft_strncmp(cmds->env[i], "OLDPWD=", 7) == 0)
		{
			free(cmds->env[i]);
			cmds->env[i] = ft_strdup(var);
		}
		else if (ft_strncmp(var, "PWD=", 4) == 0
			&& ft_strncmp(cmds->env[i], "PWD=", 4) == 0)
		{
			free(cmds->env[i]);
			cmds->env[i] = ft_strdup(var);
		}
		i++;
	}
}

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
	return (path);
}

static void	update_pwd(t_env *cmds, char *old_pwd)
{
	char	new_pwd[1024];
	char	*tmp;

	if (getcwd(new_pwd, 1024))
	{
		tmp = ft_strjoin("OLDPWD=", old_pwd);
		ft_putenv(cmds, tmp);
		free(tmp);
		tmp = ft_strjoin("PWD=", new_pwd);
		ft_putenv(cmds, tmp);
		free(tmp);
	}
	else
		perror("getcwd");
}

int	ft_cd(t_env *cmds)
{
	char	old_pwd[1024];
	char	*path;

	if ((cmds->arg[1] == NULL || cmds->arg[0] == NULL))
	{
		if (!getcwd(old_pwd, 1024))
			general_error("getcwd error.", 1, 1, cmds);
		path = get_cd_path(cmds, cmds->arg[0]);
		if (!path)
			return (1);
		if (chdir(path) != 0 && ft_strcmp(path, "-") != 0)
		{
			write(cmds->fd, "cd: no such file or directory: ", 32);
			write(cmds->fd, path, ft_strlen(path));
			write(cmds->fd, "\n", 1);
			return (1);
		}
		update_pwd(cmds, old_pwd);
	}
	else
	{
		write(cmds->fd, "cd: cant accept flags or more than 1 arg.\n", 54);
		return (2);
	}
	return (0);
}
