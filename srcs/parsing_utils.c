/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:24:47 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/27 13:22:25 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	**fake_env_creator(void)
{
	char	**new;
	char	*cwd;

	new = (char **)malloc(4 * sizeof(char *));
	if (!new)
		general_error("env malloc failed.", 0, 1, NULL);
	new[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (!new[0])
		general_error("env malloc failed.", 0, 1, NULL);
	new[1] = ft_strdup("SHLVL=1");
	if (!new[1])
		general_error("env malloc failed.", 0, 1, NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		general_error("getcwd failed.", 0, 1, NULL);
	new[2] = (char *)malloc(ft_strlen("PWD=") + ft_strlen(cwd) + 1);
	if (!new[2])
		general_error("env malloc failed.", 0, 1, NULL);
	ft_strlcpy(new[2], "PWD=", 4);
	ft_strlcat(new[2], cwd, ft_strlen(cwd));
	free(cwd);
	new[3] = NULL;
	return (new);
}

void	check_shlvl(char **new_environ, char **environ, int count)
{
	int	i;
	int	num;

	num = -1;
	i = -1;
	while (++i < count)
	{
		if (ft_strncmp(environ[i], "SHLVL=", 6) == 0)
		{
			num = ft_atoi(ft_strtrim(ft_strchr(environ[i], '='), "="));
			if (num < 0)
				num = 0;
			else
				num++;
			new_environ[i] = ft_strjoin("SHLVL=", ft_itoa(num));
		}
		else
			new_environ[i] = ft_strdup(environ[i]);
	}
	if (num == -1)
		new_environ[i++] = ft_strdup("SHLVL=1");
	new_environ[i] = NULL;
}

char	**deep_copy_environ(char **environ)
{
	char	**new_environ;
	int		count;
	int		num;

	num = -1;
	count = 0;
	while (environ[count] != NULL)
		count++;
	if (count == 0)
		new_environ = fake_env_creator();
	else
	{
		new_environ = (char **)malloc((count + 2) * sizeof(char *));
		if (!new_environ)
			general_error("env malloc failed.", 0, 1, NULL);
		check_shlvl(new_environ, environ, count);
	}
	return (new_environ);
}

void	initialize_cmd(t_env *cmd, t_env *new_cmd, int i)
{
	if (new_cmd == NULL && i == 1)
	{
		cmd->cmd = NULL;
		cmd->path = env_expander(cmd, "PATH=");
		cmd->saved_stdout = dup(1);
		cmd->saved_stdin = dup(0);
		if (cmd->path == NULL)
			cmd->path = cmd->env[0];
		cmd->arg = NULL;
		cmd->next = NULL;
		cmd->heredoc = -1;
		cmd->fd = 1;
		return ;
	}
	new_cmd->env = cmd->env;
	new_cmd->exp = cmd->exp;
	new_cmd->saved_stdout = cmd->saved_stdout;
	new_cmd->saved_stdin = cmd->saved_stdin;
	new_cmd->path = env_expander(new_cmd, "PATH=");
	new_cmd->exit_status = cmd->exit_status;
	new_cmd->heredoc = cmd->heredoc;
	new_cmd->fd = 1;
}

void	free_subtokens(char **subtokens)
{
	int	i;

	i = 0;
	if (!subtokens)
		return ;
	while (subtokens[i] != NULL)
	{
		if(subtokens[i][0])
			free(subtokens[i]);
		i++;
	}
	free(subtokens);
}
