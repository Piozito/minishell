/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:46:18 by fragarc2          #+#    #+#             */
/*   Updated: 2025/03/20 16:53:03 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static void handle_cd_error(char *path)
{
    char    *error;
    char    *tmp;

    tmp = ft_strjoin("minishell: cd: ", path);
    error = ft_strjoin(tmp, "\n");
    free(tmp);
    write(1, error, ft_strlen(error));
    free(error);
}

static char *get_cd_path(t_env *pwd, char *path)
{
    char    *home;
    char    *old_pwd;

    if (!path || !*path)
    {
        home = ft_getenv(pwd->env, "HOME");
        if (!home)
            write(1, "cd: HOME not set\n", 17);
        return (home);
    }
    if (ft_strcmp(path, "-") == 0)
    {
        old_pwd = ft_getenv(pwd->env, "OLDPWD");
        if (!old_pwd)
            write(1, "cd: OLDPWD not set\n", 19);
        return (old_pwd);
    }
    return (path);
}

static void update_pwd(t_env *pwd, char *old_pwd)
{
    char    new_pwd[PATH_MAX];
    char    *tmp;

    if (getcwd(new_pwd, PATH_MAX))
    {
        tmp = ft_strjoin("OLDPWD=", old_pwd);
        ft_putenv(pwd, tmp);
        free(tmp);
        tmp = ft_strjoin("PWD=", new_pwd);
        ft_putenv(pwd, tmp);
        free(tmp);
    }
    else
        perror("getcwd");
}

void    cd(t_env *mini, char **args)
{
    char    old_pwd[PATH_MAX];
    char    *path;

    if (!getcwd(old_pwd, PATH_MAX))
        return (perror("getcwd"));
    path = get_cd_path(mini, args[1]);
    if (!path)
        return ;
    if (chdir(path) != 0)
        handle_cd_error(path);
    else
        update_pwd(mini, old_pwd);
}