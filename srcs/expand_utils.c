/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:11:20 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/04 12:01:48 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*env_expander(t_env *cmds, char *var_name)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (cmds->env[i])
	{
		j = 0;
		if (ft_strncmp(var_name, cmds->env[i], ft_strlen(var_name)) == 0)
		{
			res = ft_strtrim(ft_strchr(cmds->env[i], '='), "=");
			while (cmds->env[i][j] != '=')
				j++;
			if (ft_strncmp(var_name, cmds->env[i], j) != 0)
				return (ft_strdup(""));
			if (res == NULL)
				return (ft_strdup(""));
			return (res);
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*var_getter(const char *input, size_t *i)
{
	int		var_index;
	char	*var_name;

	(*i)++;
	var_index = 0;
	while (input[(*i) + var_index] && input[(*i) + var_index] != ' '
		&& input[(*i) + var_index] != '$'
		&& input[(*i) + var_index] != '\t' && input[(*i) + var_index] != '\"'
		&& input[(*i) + var_index] != '\'')
		var_index++;
	var_name = (char *)malloc((var_index + 1) * sizeof(char));
	if (!var_name)
		return (NULL);
	var_index = 0;
	while (input[(*i)] && input[(*i)] != ' ' && input[(*i)] != '$'
		&& input[(*i)] != '\t' && input[(*i)] != '\"' && input[(*i)] != '\'')
		var_name[var_index++] = input[(*i)++];
	var_name[var_index] = '\0';
	return (var_name);
}

char	*var_expander(const char *input, size_t *i, t_env *cmd)
{
	char	*var_name;
	char	*expanded;

	var_name = var_getter(input, i);
	if (var_name[0] == '?' && var_name[1] == '\0')
		expanded = ft_itoa(cmd->exit_status);
	else
		expanded = env_expander(cmd, var_name);
	free(var_name);
	return (expanded);
}

void	var_joiner(char *exp, char **res, size_t *cap, size_t *len)
{
	if (exp)
	{
		if ((*len) + ft_strlen(exp) + 1 >= (*cap))
			(*res) = ft_strrealloc((*res), &(*cap));
		ft_strlcpy((*res) + (*len), exp, ft_strlen(exp) + 1);
		(*len) += ft_strlen(exp);
		free(exp);
	}
}

int	var_quote(const char *input, size_t *i, int quote)
{
	if (!quote && ft_find_closing_quote(input, *i + 1, input[*i]))
		quote = input[*i];
	else if (quote == input[*i])
		quote = 0;
	return (quote);
}
