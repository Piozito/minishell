/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:12:34 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/14 17:57:44 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char **fake_env_creator()
{
    char **new_environ;
    char *cwd;

    new_environ = (char **)malloc(4 * sizeof(char *));
    if (!new_environ)
        general_error("env malloc failed.", 0, 1, NULL);
    new_environ[0] = strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
    if (!new_environ[0])
        general_error("env malloc failed.", 0, 1, NULL);
    new_environ[1] = strdup("SHLVL=1");
    if (!new_environ[1])
        general_error("env malloc failed.", 0, 1, NULL);
    cwd = getcwd(NULL, 0);
    if (!cwd)
        general_error("getcwd failed.", 0, 1, NULL);
    new_environ[2] = (char *)malloc(strlen("PWD=") + strlen(cwd) + 1);
    if (!new_environ[2])
    {
        free(cwd);
        general_error("env malloc failed.", 0, 1, NULL);
    }
    strcpy(new_environ[2], "PWD=");
    strcat(new_environ[2], cwd);
    free(cwd);
    new_environ[3] = NULL;
    return new_environ;
}

char **deep_copy_environ(char **environ)
{
	char **new_environ;
	int count;
	int num;
	int i;

	i = -1;
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

		while (++i < count)
		{
			if (strncmp(environ[i], "SHLVL=", 6) == 0)
			{
				num = ft_atoi(ft_strtrim(ft_strchr(environ[i], '='), "="));
				if(num < 0)
					num = 0;
				else
					num++;
				new_environ[i] = ft_strjoin("SHLVL=", ft_itoa(num));
			}
			else
				new_environ[i] = ft_strdup(environ[i]);
		}
		if (num == -1)
		{
			new_environ[i++] = ft_strdup("SHLVL=1");
		}
		new_environ[i] = NULL;
	}
	return new_environ;
}

void	initialize_cmd(t_env *cmd, t_env *new_cmd, int i)
{
	if(new_cmd == NULL && i == 1)
	{
		cmd->cmd = NULL;
		cmd->path = env_expander(cmd, "PATH=");
		cmd->saved_stdout = dup(1);
		cmd->saved_stdin = dup(0);
		if(cmd->path == NULL)
			cmd->path = cmd->env[0];
		cmd->arg = NULL;
		cmd->next = NULL;
		cmd->fd = 1;
		return ;
	}
	new_cmd->env = cmd->env;
	new_cmd->exp = cmd->exp;
	new_cmd->saved_stdout = cmd->saved_stdout;
	new_cmd->saved_stdin = cmd->saved_stdin;
	new_cmd->path = env_expander(new_cmd, "PATH=");
	new_cmd->exit_status = cmd->exit_status;
	new_cmd->fd = 1;
}

void	free_subtokens(char **subtokens)
{
	int	i;

	i = 0;
	while (subtokens[i] != NULL)
	{
		free(subtokens[i]);
		i++;
	}
	free(subtokens);
}

int cmd_check(t_env *cmds)
{
	if (cmds->cmd == NULL)
		return 1;
	else if (ft_strstr(cmds->cmd, "echo") != NULL)
		return 0;
	else if (ft_strstr(cmds->cmd, "pwd") != NULL)
		return 0;
	else if (ft_strstr(cmds->cmd, "cd") != NULL)
		return 0;
	else if (ft_strstr(cmds->cmd, "env") != NULL)
		return 0;
	else if (ft_strstr(cmds->cmd, "exit") != NULL)
		return 0;
	else if (ft_strstr(cmds->cmd, "unset") != NULL)
		return 0;
	else if (ft_strstr(cmds->cmd, "export") != NULL)
		return 0;
	if (cmds->path == NULL)
	{
		cmds->path = my_get_path(cmds);
		if (cmds->path == NULL)
			cmds->exit_status = 127;
	}
	return 1;
}

void pipes_handler(t_env *cmds, const char *input)
{
    char **pipes;
    t_env *temp;
    t_env *new_cmd;
	int error = 0;
    int i;

	i = 0;
    pipes = pipe_check(cmds, input);
	if(pipes == NULL)
		return ;
	if(pipes[1] == NULL)
	{
		parsing(cmds, pipes[i]);
		pop(cmds, 0);
		free_subtokens(pipes);
		return ;
	}
    while (pipes[i] != NULL)
    {
		new_cmd = (t_env *)malloc(sizeof(t_env));
		initialize_cmd(cmds, new_cmd, 0);
        if(parsing(new_cmd, pipes[i]) == 1)
			return ;
		else
			error = 1;
        if (i == 0)
        {
            cmds = new_cmd;
            temp = cmds;
        }
        else
        {
            temp->next = new_cmd;
            temp = temp->next;
        }
        i++;
    }
    temp->next = NULL;
    temp = cmds;
    i = 0;
	cmds->exit_status = ft_pipe(cmds);
    free_subtokens(pipes);
}

int parsing(t_env *cmd, const char *input)
{
	char **subtokens;
	int arg_count = 0;
	int arg_index = 0;
	int command_set = -1;
	int j = 0;
	int k = 0;

	subtokens = ft_split_quotes(cmd, input, ' ', 1);
	if (subtokens[0] == NULL)
		return 1;
	if (ft_strchr(subtokens[0], ' ') != NULL)
	{
		command_not_found(cmd->cmd);
		free_subtokens(subtokens);
		cmd->exit_status = 127;
		return 1;
	}
	while (subtokens[j])
	{
		if (command_set == -1 && !ft_strchr(subtokens[j], '<') && !ft_strchr(subtokens[j], '>'))
		{
			if (j >= 1)
			{
				if (!ft_strchr(subtokens[j - 1], '<') && !ft_strchr(subtokens[j - 1], '>'))
					command_set = j;
			}
			else
				command_set = j;
		}
		else
		{
			while(subtokens[j][k])
			{
				if(subtokens[j][k] == '<' || subtokens[j][k] == '>')
				{
					arg_count++;
					break;
				}
				k++;
			}
			arg_count++;
		}
		j++;
	}
	cmd->arg = (char **)malloc((arg_count + 1) * sizeof(char *));
	if (!cmd->arg)
	{
		perror("Memory allocation failed.");
		free_subtokens(subtokens);
		exit(1);
	}
	j = 0;
	while (subtokens[j])
	{
		if (j == command_set)
			cmd->cmd = ft_strdup(subtokens[j]);
		else if (j < command_set)
			cmd->arg[arg_index++] = ft_strdup(subtokens[j]);
		j++;
	}
	j = command_set + 1;
	while (j > command_set && subtokens[j])
	{
		cmd->arg[arg_index++] = ft_strdup(subtokens[j++]);
	}
	cmd->arg[arg_index] = NULL;
	if(cmd_check(cmd) == 0 && ft_isalpha(cmd->cmd[0]) == 0)
	{
		command_not_found(cmd->cmd);
		free_subtokens(subtokens);
		cmd->exit_status = 127;
		return 1;
	}
	free_subtokens(subtokens);
	ft_debug(cmd);
	return 0;
}
