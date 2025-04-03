/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:12:34 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/03 15:03:23 by aaleixo-         ###   ########.fr       */
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

void pipes_handler(t_env *cmds, char *input)
{
    char **pipes;
    t_env *temp;
    t_env *new_cmd;
    int i;

    pipes = ft_split(input, '|');
    i = 0;
    while (pipes[i] != NULL)
    {
        new_cmd = (t_env *)malloc(sizeof(t_env));
        if (new_cmd == NULL)
        {
            perror("malloc");
            exit(1);
        }
        parsing(trim_spaces(pipes[i]), new_cmd);
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


void	parsing(const char *input, t_env *cmd)
{
	char	**subtokens;
	int		flag_index;
	int		arg_index;
	int		command_set;
	int		j;

	subtokens = ft_split(input, ' ');
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
			cmd->flag[flag_index++] = ft_strdup(subtokens[j]);
		else
			cmd->arg[arg_index++] = ft_strdup(subtokens[j]);
		j++;
	}
	cmd->flag[flag_index] = NULL;
	cmd->arg[arg_index] = NULL;
	free_subtokens(subtokens);
}
