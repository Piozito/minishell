/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:12:34 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/27 13:24:06 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_env	*pipes_maker(t_env *cmds, char **pipes)
{
	int		i;
	t_env	*temp;
	t_env	*new_cmd;

	i = 0;
	while (pipes[i] != NULL)
	{
		new_cmd = malloc(sizeof(t_env));
		initialize_cmd(cmds, new_cmd, 0);
		if (parsing(new_cmd, pipes[i]) == 1)
			return (NULL);
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
	return (cmds);
}

void	pipes_handler(t_env *cmds, const char *input)
{
	char	**pipes;

	pipes = pipe_check(cmds, input);
	if (pipes == NULL || pipes[0] == NULL)
		return ;
	if (pipes[1] == NULL)
	{
		if (parsing(cmds, pipes[0]) == 1)
			return ;
		pop(cmds, 0);
		free_subtokens(pipes);
		return ;
	}
	cmds = pipes_maker(cmds, pipes);
	if (cmds == NULL)
	{
		free_subtokens(pipes);
		return ;
	}
	cmds->exit_status = ft_pipe(cmds);
	free_subtokens(pipes);
}

void	command_finder(char **subtokens, int *command_set)
{
	int	j;

	j = 0;
	if ((*command_set) == -1 && !ft_strchr(subtokens[j], '<')
		&& !ft_strchr(subtokens[j], '>'))
	{
		if (j >= 1)
		{
			if (!ft_strchr(subtokens[j - 1], '<')
				&& !ft_strchr(subtokens[j - 1], '>'))
				(*command_set) = j;
		}
		else
			(*command_set) = j;
	}
}

int	arg_counter(char **subtokens, int *command_set)
{
	int	arg_count;
	int	j;
	int	k;

	j = 0;
	arg_count = 0;
	while (subtokens[j])
	{
		k = 0;
		command_finder(subtokens, command_set);
		while (subtokens[j][k])
		{
			if (subtokens[j][k] == '<' || subtokens[j][k] == '>')
			{
				arg_count++;
				break ;
			}
			k++;
		}
		arg_count++;
		j++;
	}
	return (arg_count);
}

int parsing_help(t_env *cmd, char **subtokens)
{
	if (ft_strchr(cmd->cmd, ' ') != NULL)
	{
		command_not_found(cmd->cmd);
		free_subtokens(subtokens);
		cmd->exit_status = 127;
		return (1);
	}
	return (0);
}

int	parsing(t_env *cmd, const char *input)
{
	char	**subtokens;
	int		command_set;
	int		j;

	command_set = -1;
	j = 0;
	subtokens = ft_split_quotes(cmd, input, ' ');
	if (!subtokens)
		return (1);
	cmd->arg = malloc((arg_counter(subtokens, &command_set) + 1) * 8);
	if (!cmd->arg)
		malloc_fail(subtokens);
	set_args(cmd, subtokens, command_set);
	check_heredoc(cmd);
	if (command_set == -1)
	{
		apply_fd(cmd);
		return (1);
	}
	if(parsing_help(cmd, subtokens) == 1)
		return (1);
	cmd->path = my_get_path(cmd);
	ft_debug(cmd);
	apply_heredoc(cmd);
	return (0);
}
