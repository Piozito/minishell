/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:12:34 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/12 09:42:35 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char **fake_env_creator()
{
	char **new_environ;

	new_environ = (char **)malloc(4 * sizeof(char *));
	new_environ[0] = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
	new_environ[1] = "HOME=/home/aaleixo-";
	new_environ[2] = "SHELL=/bin/minishell";
	new_environ[3] = ft_strjoin("PWD=", getcwd(NULL, 1024));
	new_environ[4] = NULL;
    if (!new_environ)
		general_error("env malloc failed.", 0, 1, NULL);
	return new_environ;
}

char **deep_copy_environ(char **environ)
{
	char **new_environ;
	int count;
	int i;

	i = -1;
	count = 0;
    while (environ[count] != NULL)
		count++;
	if(count == 0)
		new_environ = fake_env_creator();
	else
	{
    	new_environ = (char **)malloc((count + 1) * sizeof(char *));
		if (!new_environ)
			general_error("env malloc failed.", 0, 1, NULL);
		while (++i < count)
			new_environ[i] = ft_strdup(environ[i]);
		new_environ[count] = NULL;
	}
    return new_environ;
}

void	initialize_cmd(t_env *cmd, t_env *new_cmd, int i)
{
	if(new_cmd == NULL && i == 1)
	{
		cmd->cmd = NULL;
		cmd->path = getenv("PATH");
		if(cmd->path == NULL)
			cmd->path = cmd->env[0];
		cmd->arg = NULL;
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
		if(parsing(cmds, pipes[i]) == 1)
			return ;
		if(apply_fd(cmds) == 0)
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
		if(apply_fd(new_cmd) == 0)
			pop(new_cmd, 1);
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
	if (error == 0)
    	cmds->exit_status = ft_pipe(cmds);
    free_subtokens(pipes);
}

char *correct_input(const char *input)
{
	int i = 0;
	int j = 0;
	int quote = 0;
	int dquote = 0;
	char *correct_input = (char *)malloc(ft_strlen(input));

	while(input[i])
	{
		if(input[i] == '\t' && input[i] && !quote && !dquote)
		{
			correct_input[j++] = ' ';
			i++;
		}
		else
		{
			if(input[i] == '\'' && ft_find_closing_quote(input, i, '\''))
			{
				while(input[i] != '\'')
					i++;
			}
			if(input[i] == '\"' && ft_find_closing_quote(input, i, '\"'))
			{
				while(input[i] != '\"')
					i++;
			}
			correct_input[j] = input[i];
			j++;
			i++;
		}
	}
	correct_input[j] = '\0';
	return correct_input;
}

int parsing(t_env *cmd, const char *input)
{
	char **subtokens;
	int arg_count = 0;
	int arg_index = 0;
	int command_set = 0;
	int j = 0;

	subtokens = ft_split_quotes(cmd, input, ' ', 1);
	if(subtokens[0] == NULL)
		return 1;
	if(ft_strchr(subtokens[0], ' ') != NULL)
	{
		printf("command not found: %s\n", subtokens[0]);
		return 1;
	}
	while (subtokens[j])
	{
		if (!command_set)
			command_set = 1;
		else if (command_set)
			arg_count++;
		j++;
	}
	cmd->arg = (char **)malloc((arg_count + 1) * sizeof(char *));
	command_set = 0;
	if (!cmd->arg)
	{
		perror("Memory allocation failed.");
		exit(1);
	}
	j = 0;
	while (subtokens[j] != NULL)
	{
		if (!command_set)
		{
			cmd->cmd = ft_strdup(subtokens[j]);
			command_set = 1;
		}
		else
		{
			cmd->arg[arg_index++] = ft_strdup(subtokens[j]);
		}
		j++;
	}
	free_subtokens(subtokens);
	cmd->arg[arg_index] = NULL;
	ft_debug(cmd); //Remover antes de entregar (utils3.c)
	return 0;
}
