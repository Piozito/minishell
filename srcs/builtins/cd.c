/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:46:18 by fragarc2          #+#    #+#             */
/*   Updated: 2025/04/16 15:28:07 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void	ft_putenv(t_env *cmds, char *var)
{
	extern char **environ;
	int	i;

	i = 0;
	(void)cmds;
	while(environ[i])
	{
		if(ft_strncmp(var, "OLDPWD=", 7) == 0 && ft_strncmp(environ[i], "OLDPWD=", 7) == 0)
			environ[i] = var;
		else if(ft_strncmp(var, "PWD=", 4) == 0 && ft_strncmp(environ[i], "PWD=", 4) == 0)
			environ[i] = var;
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

void	ft_cd(t_env *cmds)
{
	char	old_pwd[1024];
	char	*path;
	if(cmds->arg[1] == NULL && cmds->flag[0] == NULL)
	{
		if (!getcwd(old_pwd, 1024))
			return (perror("getcwd"));
		path = get_cd_path(cmds->arg[0]);
		if (!path)
		return ;
		if (chdir(path) != 0)
			printf("cd: no such file or directory: \"%s\"\n", path);
		else
			update_pwd(cmds, old_pwd);
	}
	else
		printf("cd: cd doesn't accept flags or more than 1 argument.\n");
}
