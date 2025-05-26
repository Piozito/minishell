/* ************************************************************************** */
/*													*/
/*									  :::	::::::::   */
/*   utils2.c							 :+:	:+:	:+:   */
/*									+:+ +:+	   +:+	 */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com	+#+  +:+	 +#+	  */
/*								+#+#+#+#+#+   +#+		 */
/*   Created: 2025/04/04 17:39:06 by aaleixo-		#+#	#+#		 */
/*   Updated: 2025/05/22 12:13:07 by aaleixo-	   ###   ########.fr	 */
/*													*/
/* ************************************************************************** */

#include "../lib/minishell.h"

static int	is_separator(char ch, char c, int quote, int dquote)
{
	if (c == ' ')
		return (!quote && !dquote && (ch == c || ch == '\t' || ch == '\0'));
	return (!quote && !dquote && (ch == c || ch == '\0'));
}

char	*ft_find_closing_quote(const char *str, int start, char quote)
{
	int	i;

	i = start;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}

char *ft_strrealloc(char *result, size_t *size_ptr)
{
	char *new_result;
	size_t new_size = (*size_ptr) * 2;

	new_result = (char *)malloc(new_size * sizeof(char));
	if (!new_result)
	{
	  free(result);
	  return (NULL);
	}
	ft_strlcpy(new_result, result, *size_ptr);
	free(result);
	*size_ptr = new_size;
	return new_result;
}

static int	word_count(const char *s, char c)
{
	size_t	i;
	size_t	count;
	int	quote;
	int	dquote;

	i = 0;
	count = 0;
	quote = 0;
	dquote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !dquote)
		{
			if (quote)
				quote = 0;
			else if (ft_find_closing_quote(s, i + 1, '\''))
				quote = 1;
			i++;
			continue ;
		}
		else if (s[i] == '\"' && !quote)
		{
			if (dquote)
				dquote = 0;
			else if (ft_find_closing_quote(s, i + 1, '\"'))
				dquote = 1;
			i++;
			continue ;
		}
		else if (is_separator(s[i], c, quote, dquote))
		{
			if (!is_separator(s[i + 1], c, quote, dquote))
				count++;
		}
		i++;
	}
	if (s[0] && !is_separator(s[0], c, 0, 0))
		count++;
	return (count);
}

void pipe_quote_check(const char *input, size_t *i, int *pipe)
{
	if (input[(*i)] == '\'')
	{
		(*pipe) = 0;
		if (ft_find_closing_quote(input, (*i) + 1, '\''))
		{
			(*i)++;
			while (input[(*i)] != '\'')
				(*i)++;
		}
	}
	else if (input[(*i)] == '\"')
	{
		(*pipe) = 0;
		if (ft_find_closing_quote(input, (*i) + 1, '\"'))
		{
			(*i)++;
			while (input[(*i)] != '\"')
				(*i)++;
		}
	}
}

char	**pipe_check(t_env *cmds, const char *input)
{
	size_t	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"')
			pipe_quote_check(input, &i, &pipe);
		else if (input[i] == '|' || input[0] == '|')
		{
			if (pipe == 1)
				break;
			else
				pipe = 1;
		}
		else if (input[i] != ' ' && input[i] != '|' && input[i] != '\t' && input[i] != '\0')
			pipe = 0;
		i++;
	}
	if (pipe == 1)
		if(general_error("Parsing pipe error.", 1, 0, cmds))
			return NULL;
	return (ft_split_quotes(cmds, input, '|'));
}

int handle_quote(const char *s, size_t *index, int *quote_flag)
{
	if (*quote_flag == 0 && ((s[(*index)] == '\'' && s[(*index) + 1] == '\'') || (s[(*index)] == '\"' && s[(*index) + 1] == '\"')))
	{
		index += 2;
		return 0;
	}
    if ((*quote_flag == 0) && (s[*index] == '\'' || s[*index] == '\"'))
	{
        if (ft_find_closing_quote(s, *index + 1, s[*index]))
            *quote_flag = s[*index];
        return 0;
    }
    if (*quote_flag && s[*index] == *quote_flag)
        *quote_flag = 0;
    return 0;
}

static char	*extract_word(t_env *cmds, const char *s, size_t *index, char delimiter)
{
	char	*result;
	size_t	allocated_size;
	size_t	i;
	int		quote;

	allocated_size = 1024;
	quote = 0;
	i = 0;
	result = malloc(allocated_size);
	if (!result)
		return NULL;
	while (s[*index] && !is_separator(s[*index], delimiter, quote, quote))
	{
		if(s[*index] == '<' || s[*index] == '>')
		{
			if(delimiter == '|' && s[*index] == '<' && s[*index + 1] == '<')
			{
				if(check_heredoc(cmds, s, index))
					return NULL;
			}
			if(delimiter == '|')
				result[i++] = ' ';
			result[i++] = s[(*index)++];
			if(s[*index] == '<' || s[*index] == '>')
				result[i++] = s[(*index)++];
			if(delimiter == '|')
				result[i++] = ' ';
		}
		else if (handle_quote(s, index, &quote))
			continue;
		else
			result[i++] = s[(*index)++];
		if (i >= allocated_size - 1)
		{
			result = ft_strrealloc(result, &allocated_size);
			if (!result)
			    return NULL;
		}
	}
	result[i] = '\0';
	return result;
}

void	remove_closed_quotes(char **result)
{
	int		i;
	int		j;
	int		k;
	int		quote;
	char	*new;

	i = 0;
	while (result[i])
	{
		j = 0;
		k = 0;
		quote = 0;
		new = malloc(ft_strlen(result[i]) + 1);
		if (!new)
			return ;
		while (result[i][j])
		{
			if (!quote && (result[i][j] == '\'' || result[i][j] == '\"')
				&& ft_find_closing_quote(result[i], j + 1, result[i][j]))
			{
				quote = result[i][j];
				j++;
				continue;
			}
			if (quote && result[i][j] == quote)
			{
				quote = 0;
				j++;
				continue;
			}
			new[k++] = result[i][j++];
		}
		new[k] = '\0';
		free(result[i]);
		result[i] = new;
		i++;
	}
}

int	check_redirs(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		if (result[i][0] == '<' || result[i][0] == '>')
		{
			if ((result[i][1] == '<' || result[i][1] == '>') &&
				(result[i][2] == '<' || result[i][2] == '>'))
				return (1);
			if (result[i][1] && (result[i][1] == '<' || result[i][1] == '>') &&
				result[i][0] != result[i][1])
				return (1);
			if ((!result[i][1] && !result[i + 1]) ||
				(result[i][1] && (result[i][1] == '<' || result[i][1] == '>') &&
				!result[i][2] && !result[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

char **ft_split_quotes(t_env *cmd, const char *s, char delimiter)
{
	char **result;
	size_t i;
	size_t index;
	size_t words;

	i = 0;
	index = 0;
	words = word_count(s, delimiter);
	if (!s)
	  return (NULL);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
	  return (NULL);
	while (i < words)
	{
	  while (s[index] && is_separator(s[index], delimiter, 0, 0))
		index++;
	  if (s[index] && !is_separator(s[index], delimiter, 0, 0))
	  {
		result[i] = extract_word(cmd, s, &index, delimiter);
		if(!result[i])
			return NULL;
	  }
	  i++;
	}
	result[i] = NULL;
	if(ft_strchr(s, '$') != NULL && delimiter == '|')
		expand_variables(cmd, result);
	if(delimiter == ' ')
		remove_closed_quotes(result);
	if(check_redirs(result) == 1)
	{
		general_error("Redirection parsing error.", 1, 0, cmd);
		return NULL;
	}
	return (result);
}
