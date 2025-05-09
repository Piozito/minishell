/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:12:34 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/09 09:59:30 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char **deep_copy_environ(char **environ)
{
	int count;
	int i;

	i = -1;
	count = 0;
    while (environ[count] != NULL)
        count++;
    char **new_environ = (char **)malloc((count + 1) * sizeof(char *));
    if (!new_environ)
		general_error("env malloc failed.", 0, NULL);
 	while (++i < count)
        new_environ[i] = ft_strdup(environ[i]);
    new_environ[count] = NULL;
    return new_environ;
}

void	initialize_cmd(t_env *cmd, t_env *new_cmd, int i)
{
	if(new_cmd == NULL && i == 1)
	{
		cmd->cmd = NULL;
		cmd->path = getenv("PATH");
		cmd->arg = NULL;
		cmd->flag = NULL;
		cmd->next = NULL;
		cmd->fd = 1;
		return ;
	}
	new_cmd->path = cmd->path;
	new_cmd->env = cmd->env;
	new_cmd->exp = cmd->exp;
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

char *trim_spaces(char *str)
{
    char *end;
    while (*str == ' ')
		str++;
    if (*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
		end--;
    *(end + 1) = 0;
    return str;
}

int cmd_check(t_env *cmds)
{
	if (ft_strstr(cmds->cmd, "echo") != NULL)
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
		cmds->path = my_get_path(cmds->cmd);
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
    int i;

	i = 0;
    pipes = pipe_check(cmds, input);
	if(pipes == NULL)
		return ;
    while (pipes[i] != NULL)
    {
		new_cmd = (t_env *)malloc(sizeof(t_env));
		initialize_cmd(cmds, new_cmd, 0);
        parsing(new_cmd, pipes[i]);
		if(apply_fd(new_cmd) == 1)
			return ;
		pop(new_cmd, 1);
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
    ft_pipe(cmds);
    free_subtokens(pipes);
}

void parsing(t_env *cmd, const char *input)
{
	char **subtokens;
	int flag_count = 0;
	int arg_count = 0;
	int flag_index = 0;
	int arg_index = 0;
	int command_set = 0;
	int j = 0;

	subtokens = ft_split_quotes(cmd, input, ' ', 1);

	while (subtokens[j])
	{
		if (!command_set)
			command_set = 1;
		else if (subtokens[j][0] == '-')
			flag_count++;
		else if (command_set)
			arg_count++;
		j++;
	}
	cmd->flag = (char **)malloc((flag_count + 1) * sizeof(char *));
	cmd->arg = (char **)malloc((arg_count + 1) * sizeof(char *));
	command_set = 0;
	if (!cmd->flag || !cmd->arg)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (subtokens[j] != NULL)
	{
		if (!command_set)
		{
			cmd->cmd = ft_strdup(subtokens[j]);
			command_set = 1;
		}
		else if (subtokens[j][0] == '-' && flag_count > 0)
		{
			cmd->flag[flag_index++] = ft_strdup(subtokens[j]);
		}
		else if (arg_count > 0)
		{
			cmd->arg[arg_index++] = ft_strdup(subtokens[j]);
		}
		j++;
	}
	cmd->flag[flag_index] = NULL;
	cmd->arg[arg_index] = NULL;
	ft_debug(cmd); //Remover antes de entregar (utils3.c)
	free_subtokens(subtokens);
}
