/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   expand.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/07 13:22:32 by fragarc2		  #+#	#+#			 */
/*   Updated: 2025/05/20 16:06:28 by aaleixo-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../lib/minishell.h"

void	exp_line(const char *input, size_t *cap, char **res, t_env *cmd)
{
	size_t	i;
	size_t	j;
	int		quote;

	i = 0;
	j = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			quote = var_quote(input, &i, quote);
		if (quote != '\'' && input[i] == '$' && input[i + 1]
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

char	*expand_string_variables(t_env *cmd, const char *input)
{
	size_t	cap;
	char	*res;

	cap = ft_strlen(input) + 1024;
	res = malloc(cap);
	if (!res)
		return (NULL);
	exp_line(input, &cap, &res, cmd);
	return (res);
}

void	expand_variables(t_env *cmd, char **result)
{
	size_t	i;
	char	*expanded;

	i = 0;
	if (!result)
		return ;
	while (result[i] != NULL)
	{
		expanded = expand_string_variables(cmd, result[i]);
		if (expanded)
		{
			free(result[i]);
			result[i] = expanded;
		}
		i++;
	}
}
