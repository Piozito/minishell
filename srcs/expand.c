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

char *env_expander(t_env *cmds, char *var_name)
{
	int i = 0;
	int j = 0;
	char *res = NULL;
	while (cmds->env[i])
	{
		j = 0;
		if(ft_strncmp(var_name, cmds->env[i], ft_strlen(var_name)) == 0)
		{
			res = ft_strtrim(ft_strchr(cmds->env[i], '='), "=");
			while(cmds->env[i][j] != '=')
				j++;
			if(ft_strncmp(var_name, cmds->env[i], j) != 0)
				return ft_strdup("");
			if(res == NULL)
				return ft_strdup("");
			return res;
		}
		i++;
	}
	return ft_strdup("");
}

char *expand_string_variables(t_env *cmd, const char *input)
{
	size_t result_capacity = ft_strlen(input) + 1024;
	char *result = malloc(result_capacity);
	size_t result_len = 0;
	char *expanded;

	size_t i = 0;
	int quote = 0;
	int dquote = 0;
	char *var_name = NULL;
	size_t var_index = 0;
	if (!result)
		return NULL;
	while (input[i])
	{
		if (input[i] == '\'' && !dquote && ft_find_closing_quote(input, i + 1, '\''))
		{
			quote = !quote;
			result[result_len++] = input[i++];
		}
		else if (input[i] == '\"' && !quote  && ft_find_closing_quote(input, i + 1, '\"'))
		{
			dquote = !dquote;
			result[result_len++] = input[i++];
		}
		else if (!quote && input[i] == '$' && input[i + 1] && ft_isprint(input[i + 1]) && input[i + 1] != ' ' && input[i + 1] != '\t')
		{
			i++;
			var_index = 0;
			while (input[i + var_index] && input[i + var_index] != ' ' && input[i + var_index] != '$' && 
				   input[i + var_index] != '\t' && input[i + var_index] != '\"' && input[i + var_index] != '\'')
				var_index++;
			var_name = (char *)malloc((var_index + 1) * sizeof(char));
			if (!var_name)
			{
				free(result);
				return NULL;
			}
			var_index = 0;
			while (input[i] && input[i] != ' ' && input[i] != '$' && 
				   input[i] != '\t' && input[i] != '\"' && input[i] != '\'')
				var_name[var_index++] = input[i++];
			var_name[var_index] = '\0';
			if (var_name[0] == '?' && var_name[1] == '\0')
				expanded = ft_itoa(cmd->exit_status);
			else
				expanded = env_expander(cmd, var_name);
			free(var_name);
			if (expanded)
			{
				if (result_len + ft_strlen(expanded) + 1 >= result_capacity)
					result = ft_strrealloc(result, &result_capacity);
				ft_strlcpy(result + result_len, expanded, ft_strlen(expanded) + 1);
				result_len += ft_strlen(expanded);
				free(expanded);
			}
		}
		else if(result_len + 2 >= result_capacity)
			result = ft_strrealloc(result, &result_capacity);
		else
			result[result_len++] = input[i++];
	}
	result[result_len] = '\0';
	return result;
}

void expand_variables(t_env *cmd, char **result)
{
	size_t i = 0;
	char *expanded;

	if (!result)
		return;
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
