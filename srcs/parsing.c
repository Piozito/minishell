/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:12:34 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/21 16:08:09 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char **deep_copy_environ()
{
	extern char **environ;
	int count = 0;
    while (environ[count] != NULL) {
        count++;
    }
    char **new_environ = (char **)malloc((count + 1) * sizeof(char *));
    if (new_environ == NULL) {
        perror("Failed to allocate memory for new_environ");
        return NULL;
    }
    for (int i = 0; i < count; i++) {
        new_environ[i] = ft_strdup(environ[i]);
    }
    new_environ[count] = NULL;
    return new_environ;
}

void	initialize_cmd(t_env *cmd, t_env *new_cmd, int i)
{
	extern char **environ;

	if(new_cmd == NULL && i == 1)
	{
		cmd->cmd = NULL;
		cmd->path = getenv("PATH");
		if(environ[0] == NULL)
		{
			cmd->exp = NULL;
			cmd->env = NULL;
		}
		else
		{
			cmd->exp = deep_copy_environ();
			cmd->env = deep_copy_environ();
		}
		cmd->arg = NULL;
		cmd->flag = NULL;
		cmd->next = NULL;
		cmd->exit_status = 0;
		return ;
	}
	new_cmd->path = cmd->path;
	new_cmd->env = cmd->env;
	new_cmd->exp = cmd->exp;
	new_cmd->exit_status = 0;
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
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		return 0;
	else if (ft_strcmp(cmds->cmd, "pwd") == 0)
		return 0;
	else if (ft_strcmp(cmds->cmd, "cd") == 0)
		return 0;
	else if (ft_strcmp(cmds->cmd, "env") == 0)
		return 0;
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		return 0;
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		return 0;
	else if (ft_strcmp(cmds->cmd, "export") == 0)
		return 0;
	else
	{
		cmds->path = my_get_path(cmds->cmd);
		if (cmds->path == NULL)
		{
			printf("command not found: \"%s\"\n", cmds->cmd);
			return 1;
		}
	}
}

void pipes_handler(t_env *cmds, const char *input)
{
    char **pipes;
    t_env *temp;
    t_env *new_cmd;
    int i;

	i = 0;
    pipes = pipe_check(input);
	if(pipes == NULL)
		return ;
	if(pipes[1] == NULL)
	{
		parsing(cmds, pipes[i]);
		if(cmd_check(cmds) == 0)
			//funcao poggers
		else
		{
			apply_redirections(cmds);
			ft_exec(cmds);
		}
		free_subtokens(pipes);
		return ;
	}
    while (pipes[i] != NULL)
    {
		new_cmd = (t_env *)malloc(sizeof(t_env));
		initialize_cmd(cmds, new_cmd, 1);
        parsing(new_cmd, pipes[i]);
		if(cmd_check(cmds) == 0)
			//funcao poggers
		else
		{
			apply_redirections(cmds);
			ft_exec(cmds);
		}
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

	subtokens = ft_split_quotes(input, ' ', 1);

	for (j = 0; subtokens[j] != NULL; j++)
	{
		if (!command_set)
			command_set = 1;
		else if (subtokens[j][0] == '-')
			flag_count++;
		else if (command_set)
			arg_count++;
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