/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_heredoc_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:49:33 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/04 13:26:05 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*concatenate_strings(char **strings)
{
	size_t	total_length;
	size_t	i;
	char	*result;

	i = 0;
	total_length = 0;
	if (strings == NULL)
		return (NULL);
	while (strings[i] != NULL)
	{
		total_length += ft_strlen(strings[i]);
		i++;
	}
	result = (char *)malloc(total_length + 1);
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (strings[i] != NULL)
	{
		ft_strlcat(result, strings[i], total_length + 1);
		i++;
	}
	return (result);
}

void	hc_exp_line(const char *input, size_t *cap, char **res, t_env *cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1]
			&& ft_isprint(input[i + 1]) && input[i + 1] != ' '
			&& input[i + 1] != '\t')
			var_joiner(var_expander(input, &i, cmd), res, cap, &j);
		else
			(*res)[j++] = input[i++];
		if (j + 2 >= (*cap))
			(*res) = ft_strrealloc((*res), cap);
	}
	(*res)[j] = '\0';
}

char	*hc_expand(t_env *cmd, const char *input)
{
	char	*res;
	size_t	cap;
	size_t	i;

	i = 0;
	cap = 0;
	while (cmd->env[i])
	{
		if (ft_strlen(cmd->env[i]) > cap)
			cap = ft_strlen(cmd->env[i]);
		i++;
	}
	res = malloc(cap);
	if (!res)
		return (NULL);
	hc_exp_line(input, &cap, &res, cmd);
	return (res);
}
