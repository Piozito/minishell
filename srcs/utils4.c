/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:39:09 by fragarc2          #+#    #+#             */
/*   Updated: 2025/05/26 12:50:21 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	if (*big == '\0')
		return (NULL);
	i = 0;
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

void command_not_found(char *cmd)
{
	char *full_str;

	full_str = ft_strjoin("command not found: \"", cmd);
	full_str = ft_strjoin(full_str, "\"\n");
	write(2, full_str, ft_strlen(full_str));
	free(full_str);
}

int executable_check(t_env *cmds)
{
	int i = 0;
	if(!cmds->cmd && cmds->arg[0])
	{
		if(!cmds->arg[1])
			return 1;
		if(ft_strncmp(cmds->arg[0], ">", 1) == 0 || ft_strncmp(cmds->arg[1], "<", 1) == 0)
		{
			apply_fd(cmds);
		}
		return 1;
	}
	while(cmds->cmd[i])
	{
		if(ft_isalpha(cmds->cmd[i]) == 1)
			return 0;
		i++;
	}
	return 1;
}

char *get_file(const char *s, size_t *index)
{
    char *res = NULL;
	size_t i;
    size_t start;
	size_t length;

	i = -1;
	(*index)++;
	if(s[(*index)] == '>' || s[(*index)] == '<')
		(*index)++;
    while (s[(*index)] == ' ' || s[(*index)] == '\t')
        (*index)++;
    start = (*index);
    while (s[(*index)] && s[(*index)] != ' ' && s[(*index)] != '\t' 
	&& s[(*index)] != '\'' && s[(*index)] != '\"' && s[(*index)] != '<' && s[(*index)] != '>')
        (*index)++;
    length = (*index) - start;
    res = (char *)malloc((length + 1) * sizeof(char));
    if (!res)
        return NULL;
    while (++i < length)
        res[i] = s[start + i];
    res[length] = '\0';
	if(res[0] == '\0')
		return NULL;
    return res;
}
