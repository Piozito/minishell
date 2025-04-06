/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:12:34 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/04 19:28:43 by aaleixo-         ###   ########.fr       */
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

int pipe_check(const char *input)
{
	int i;
	int command_set;

	i = 0;
	command_set = 0;
	while(input[i] != '\0')
	{
		if(input[i] == '|')
		{
			if(command_set == 0)
			{
				printf("pipe: no command before pipe.\n");
				return 1;
			}
			command_set = 0;
		}
		else if(input[i] != ' ' && input[i] != '|')
			command_set = 1;
		i++;
	}
	return 0;
}

void pipes_handler(t_env *cmds, const char *input)
{
    char **pipes;
    t_env *temp;
    t_env *new_cmd;
    int i;

	i = 0;
    pipes = ft_split_quotes(input, '|');
	if(pipes[1] == NULL)
	{
		parsing(cmds, input);
		check_builtin(cmds);
		return ;
	}
    while (pipes[i] != NULL)
    {
        new_cmd = (t_env *)malloc(sizeof(t_env));
        parsing(new_cmd, trim_spaces(pipes[i]));
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
