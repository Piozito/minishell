/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:12:34 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/03/31 11:12:58 by aaleixo-         ###   ########.fr       */
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
