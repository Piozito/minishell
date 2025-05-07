/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:46:18 by fragarc2          #+#    #+#             */
/*   Updated: 2025/05/07 12:15:54 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void	ft_putenv(t_env *cmds, char *var)
{
	int	i;

	i = 0;
	(void)cmds;
	while(cmds->env[i])
	{
		if(ft_strncmp(var, "OLDPWD=", 7) == 0 && ft_strncmp(cmds->env[i], "OLDPWD=", 7) == 0)
			cmds->env[i] = var;
		else if(ft_strncmp(var, "PWD=", 4) == 0 && ft_strncmp(cmds->env[i], "PWD=", 4) == 0)
			cmds->env[i] = var;
		i++;
	}
}

static char	*get_cd_path(char *path)
{
	char	*home;
	char	*old_pwd;

	if (!path || !*path)
	{
		home = getenv("HOME");
		return (home);
	}
	if (ft_strcmp(path, "-") == 0)
	{
		old_pwd = getenv("OLDPWD");
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
	if((cmds->arg[1] == NULL || cmds->arg[0] == NULL) && cmds->flag[0] == NULL)
	{
		if (!getcwd(old_pwd, 1024))
		{
			perror("getcwd");
			return (1);
		}
		path = get_cd_path(cmds->arg[0]);
		if (!path)
			return(1);
		if (chdir(path) != 0)
		{
			write(cmds->fd, "cd: no such file or directory:\n", 32);
			write(cmds->fd, path, ft_strlen(path));
			return(2);
		}
		else
			update_pwd(cmds, old_pwd);
	}
	else
	{
		write(cmds->fd, "cd: cd doesn't accept flags or more than 1 argument.\n", 54);
		return(2);
	}

	return(0);
}
