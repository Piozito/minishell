/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:12:34 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/14 14:21:24 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	initialize_cmd(t_env *cmd)
{
	int	i;

	cmd->cmd = NULL;
	i = 0;
	while (i < MAX_FLAGS)
		cmd->flag[i++] = NULL;
	i = 0;
	while (i < MAX_ARGS)
		cmd->arg[i++] = NULL;
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
		parsing(cmds, input);
		cmd_check(cmds);
		apply_redirections(cmds);
		check_builtin(cmds);
		return ;
	}
    while (pipes[i] != NULL)
    {
        new_cmd = (t_env *)malloc(sizeof(t_env));
        parsing(new_cmd, trim_spaces(pipes[i]));
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
    int flag_index;
    int arg_index;
    int command_set;
    int j;

    subtokens = ft_split_quotes(input, ' ');
	flag_index = 0;
    arg_index = 0;
    command_set = 0;
    j = 0;
    initialize_cmd(cmd);
    while (subtokens[j] != NULL)
    {
        if (!command_set)
        {
            cmd->cmd = ft_strdup(subtokens[j]);
            command_set = 1;
        }
        else if (subtokens[j][0] == '-')
        {
            cmd->flag[flag_index] = ft_strdup(subtokens[j]);
            flag_index++;
        }
        else
        {
            cmd->arg[arg_index] = ft_strdup(subtokens[j]);
            arg_index++;
        }
        j++;
    }
    cmd->flag[flag_index] = NULL;
    cmd->arg[arg_index] = NULL;
    free_subtokens(subtokens);
}