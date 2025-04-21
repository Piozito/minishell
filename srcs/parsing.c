/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:12:34 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/21 11:50:25 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	initialize_cmd(t_env *cmd)
{
	extern char **environ;

	cmd->cmd = NULL;
	cmd->arg = NULL;
	cmd->path = getenv("PATH");
	if(environ[0] == NULL)
		cmd->env = NULL;
	else
		cmd->env = environ;
	cmd->flag = NULL;
	cmd->next = NULL;
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
    while (isspace((unsigned char)*str))
		str++;
    if (*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
		end--;
    *(end + 1) = 0;
    return str;
}

void cmd_check(t_env *cmds)
{
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		(void)cmds->cmd;
	else if (ft_strcmp(cmds->cmd, "pwd") == 0)
		(void)cmds->cmd;
	else if (ft_strcmp(cmds->cmd, "cd") == 0)
		(void)cmds->cmd;
	else if (ft_strcmp(cmds->cmd, "env") == 0)
		(void)cmds->cmd;
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		(void)cmds->cmd;
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		(void)cmds->cmd;
	else if (ft_strcmp(cmds->cmd, "export") == 0)
		(void)cmds->cmd;
	else
	{
		cmds->path = my_get_path(cmds->cmd);
		if (cmds->path == NULL)
		{
			printf("command not found: \"%s\"\n", cmds->cmd);
			return ;
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
		cmd_check(cmds);
		check_builtin(cmds);
		apply_redirections(cmds);
		free_subtokens(pipes);
		return ;
	}
    while (pipes[i] != NULL)
    {
        new_cmd = (t_env *)malloc(sizeof(t_env));
        parsing(new_cmd, pipes[i]);
		cmd_check(new_cmd);
		apply_redirections(new_cmd);
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
	initialize_cmd(cmd);
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
