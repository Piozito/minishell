/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:12:34 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/02 16:28:13 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_env	*pipes_maker(t_env *cmds, char **pipes)
{
	int		i;
	t_env	*temp;
	t_env	*new_cmd;

	if (parsing(cmds, pipes[0]) == 1)
		return (NULL);
	temp = cmds;
	i = 1;
	while (pipes[i] != NULL)
	{
		new_cmd = malloc(sizeof(t_env));
		initialize_cmd(cmds, new_cmd, 0);
		if (parsing(new_cmd, pipes[i]) == 1)
			return (NULL);
		temp->next = new_cmd;
		temp = temp->next;
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

int	parsing_help(t_env *cmd, char **subtokens, int command_set)
{
	if (command_set == -1)
	{
		apply_fd(cmd);
		return (0);
	}
	if (ft_strchr(cmd->cmd, ' ') != NULL)
	{
		command_not_found(cmd->cmd);
		free_subtokens(subtokens);
		cmd->exit_status = 127;
		return (1);
	}
	return (0);
}

void	command_finder(char **subtokens, int *command_set)
{
	int	j;

	j = 0;
	*command_set = -1;
	while (subtokens[j])
	{
		if (ft_strchr(subtokens[j], '<') || ft_strchr(subtokens[j], '>'))
		{
			j += 2;
			continue ;
		}
		*command_set = j;
		break ;
	}
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
	if (parsing_help(cmd, subtokens, command_set) == 1)
		return (1);
	cmd->path = my_get_path(cmd);
	apply_heredoc(cmd);
	free_subtokens(subtokens);
	ft_debug(cmd);
	return (0);
}
